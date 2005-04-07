/*
cpaf::App base application class
*/

/*
cpaf::App system overview

cpaf::main()
	Called by the library, implemented by an application. The purpose of this function is
    to return a cpaf::App derived object which will be used to run the application.
cpaf::App
	Base application class. A specialized form is used to actually have an application/
cpaf::gui::App
	GUI application class, inherits from cpaf::App
cpaf::console::App
	Console application, inherits from cpaf::App
cpaf::App::run()
	Pure virtual function used to "run" an application. In cpaf::console::App, this function
    is implemented by a client code derivative and is used instead of int main(). For cpaf::gui::App,
    this function is implemented private to the library by an implementation and contains the platform
    specific message loop or what ever else is needed to run a GUI app on that system.
cpaf::App::init()
	Pure virtual function and is expected to be implemented by a client code derivative. The
    purpose of this function in a GUI app is to create the main application windows and perform
    other related initialization tasks. The purpose in a console app is mainly for initialization
    tasks before cpaf::App::run() is called. Analagous to wxApp::OnInit().

*/
#ifndef CPAF_APP_H
#define CPAF_APP_H

#include <cpaf/dllimpexp.h>

namespace cpaf {

class CPAF_EXP App
{
public:
    //! \todo Should I make this not an inilined dtor?
    virtual ~App() { }

    virtual bool init() = 0;
    virtual int run() = 0;
};

} // cpaf

#endif // CPAF_APP_H
