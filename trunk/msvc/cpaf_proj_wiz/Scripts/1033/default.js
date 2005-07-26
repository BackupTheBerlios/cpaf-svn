
function OnFinish(selProj, selObj)
{
	try
	{
		var strProjectPath = wizard.FindSymbol('PROJECT_PATH');
		var strProjectName = wizard.FindSymbol('PROJECT_NAME');

		selProj = CreateCustomProject(strProjectName, strProjectPath);
		AddConfig(selProj, strProjectName);
		AddFilters(selProj);

		var InfFile = CreateCustomInfFile();
		AddFilesToCustomProj(selProj, strProjectName, strProjectPath, InfFile);
		PchSettings(selProj);
		InfFile.Delete();

		selProj.Object.Save();
	}
	catch(e)
	{
		if (e.description.length != 0)
			SetErrorInfo(e);
		return e.number
	}
}

function CreateCustomProject(strProjectName, strProjectPath)
{
	try
	{
		var strProjTemplatePath = wizard.FindSymbol('PROJECT_TEMPLATE_PATH');
		var strProjTemplate = '';
		strProjTemplate = strProjTemplatePath + '\\default.vcproj';

		var Solution = dte.Solution;
		var strSolutionName = "";
		if (wizard.FindSymbol("CLOSE_SOLUTION"))
		{
			Solution.Close();
			strSolutionName = wizard.FindSymbol("VS_SOLUTION_NAME");
			if (strSolutionName.length)
			{
				var strSolutionPath = strProjectPath.substr(0, strProjectPath.length - strProjectName.length);
				Solution.Create(strSolutionPath, strSolutionName);
			}
		}

		var strProjectNameWithExt = '';
		strProjectNameWithExt = strProjectName + '.vcproj';

		var oTarget = wizard.FindSymbol("TARGET");
		var prj;
		if (wizard.FindSymbol("WIZARD_TYPE") == vsWizardAddSubProject)  // vsWizardAddSubProject
		{
			var prjItem = oTarget.AddFromTemplate(strProjTemplate, strProjectNameWithExt);
			prj = prjItem.SubProject;
		}
		else
		{
			prj = oTarget.AddFromTemplate(strProjTemplate, strProjectPath, strProjectNameWithExt);
		}
		return prj;
	}
	catch(e)
	{
		throw e;
	}
}

function AddFilters(proj)
{
	try
	{
		// Add the folders to your project
		var source = 'cpp\;c\;cxx\;def\;odl\;idl\;hpj\;bat\;asm\;asmx';
		var header = 'h\;hpp\;hxx\;hm\;inl\;inc\;xsd';
		var resource = 'rc\;ico\;cur\;bmp\;dlg\;rc2\;rct\;bin\;rgs\;gif\;jpg\;jpeg\;jpe\;resx';
		
		var group = proj.Object.AddFilter('Source Files');
		group.Filter = source;
		group = proj.Object.AddFilter('Header Files');
		group.Filter = header;
		group = proj.Object.AddFilter('Resource Files');
		group.Filter = resource;
	}
	catch(e)
	{
		throw e;
	}
}

function AddConfig(proj, strProjectName)
{
	try
	{
		proj.Object.AddConfiguration('debug dll');
		proj.Object.AddConfiguration('debug static lib');
		proj.Object.AddConfiguration('release dll');
		proj.Object.AddConfiguration('release static lib');
		
		var debug = proj.Object.Configurations('Debug');
		var release = proj.Object.Configurations('Release');
		
		var config = proj.Object.Configurations('debug dll');
		debug.CopyTo(config);
		AddCompilerConfig(proj, config, true, true);
		
		config = proj.Object.Configurations('debug static lib');
		debug.CopyTo(config);
		AddCompilerConfig(proj, config, false, true);
		
		config = proj.Object.Configurations('release dll');
		release.CopyTo(config);
		AddCompilerConfig(proj, config, true, false);
		
		config = proj.Object.Configurations('release static lib');
		release.CopyTo(config);
		AddCompilerConfig(proj, config, false, false);

		proj.Object.RemoveConfiguration(debug);
		proj.Object.RemoveConfiguration(release);
	}
	catch(e)
	{
		throw e;
	}
}

function AddCompilerConfig(proj, config, dll, debug)
{
	config.IntermediateDirectory = '$(ConfigurationName)';
	config.OutputDirectory = '$(ConfigurationName)';

	if( dll )
		config.DebugSettings.WorkingDirectory = '$(CPAF_DIR)\\lib';

	var compiler_tool = config.Tools('VCCLCompilerTool');
	compiler_tool.RuntimeTypeInfo = true;
	compiler_tool.Warninglevel = warninglevelOption.warningLevel_3;

	var pp = 'CPAF_WIN32\;WIN32\;_WINDOWS\;';
	if( debug )
		pp += '_DEBUG\;';
	if( dll )
		pp += 'CPAF_DLL\;';
	
	compiler_tool.PreprocessorDefinitions = pp;

	if( debug )
		compiler_tool.MinimalRebuild = true;

	var rtl;
	if( debug )
		rtl = runtimeLibraryOption.rtMultiThreadedDebugDLL;
	else
		rtl = runtimeLibraryOption.rtMultiThreadedDLL;
	compiler_tool.RuntimeLibrary = rtl;

	compiler_tool.UsePrecompiledHeader = pchOption.pchGenerateAuto;
	
	if( debug )
		compiler_tool.DebugInformationFormat = debugOption.debugEditAndContinue;
	
	var linker_tool = config.Tools('VCLinkerTool');
	
	var input = 'cpaf-gui-win32';
	if( debug )
		input += 'd';
	if( dll )
		input += '-dll';
	input += '.lib';
	linker_tool.AdditionalDependencies = input;
	
	if( debug )
		linker_tool.GenerateDebugInformation = true;
}

function PchSettings(proj)
{
	// TODO: specify pch settings
}

function DelFile(fso, strWizTempFile)
{
	try
	{
		if (fso.FileExists(strWizTempFile))
		{
			var tmpFile = fso.GetFile(strWizTempFile);
			tmpFile.Delete();
		}
	}
	catch(e)
	{
		throw e;
	}
}

function CreateCustomInfFile()
{
	try
	{
		var fso, TemplatesFolder, TemplateFiles, strTemplate;
		fso = new ActiveXObject('Scripting.FileSystemObject');

		var TemporaryFolder = 2;
		var tfolder = fso.GetSpecialFolder(TemporaryFolder);
		var strTempFolder = tfolder.Drive + '\\' + tfolder.Name;

		var strWizTempFile = strTempFolder + "\\" + fso.GetTempName();

		var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');
		var strInfFile = strTemplatePath + '\\Templates.inf';
		wizard.RenderTemplate(strInfFile, strWizTempFile);

		var WizTempFile = fso.GetFile(strWizTempFile);
		return WizTempFile;
	}
	catch(e)
	{
		throw e;
	}
}

function GetTargetName(strName, strProjectName)
{
	try
	{
		// TODO: set the name of the rendered file based on the template filename
		var strTarget = strName;

		if (strName == 'readme.txt')
			strTarget = 'ReadMe.txt';

		if (strName == 'sample.txt')
			strTarget = 'Sample.txt';

		return strTarget; 
	}
	catch(e)
	{
		throw e;
	}
}

function AddFilesToCustomProj(proj, strProjectName, strProjectPath, InfFile)
{
	try
	{
		var projItems = proj.ProjectItems

		var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');

		var strTpl = '';
		var strName = '';

		var strTextStream = InfFile.OpenAsTextStream(1, -2);
		while (!strTextStream.AtEndOfStream)
		{
			strTpl = strTextStream.ReadLine();
			if (strTpl != '')
			{
				strName = strTpl;
				var strTarget = GetTargetName(strName, strProjectName);
				var strTemplate = strTemplatePath + '\\' + strTpl;
				var strFile = strProjectPath + '\\' + strTarget;

				var bCopyOnly = false;  //"true" will only copy the file from strTemplate to strTarget without rendering/adding to the project
				var strExt = strName.substr(strName.lastIndexOf("."));
				if(strExt==".bmp" || strExt==".ico" || strExt==".gif" || strExt==".rtf" || strExt==".css")
					bCopyOnly = true;
				wizard.RenderTemplate(strTemplate, strFile, bCopyOnly);
				proj.Object.AddFile(strFile);
			}
		}
		strTextStream.Close();
	}
	catch(e)
	{
		throw e;
	}
}
