/*
cpaf::String implementation
*/

#include <cpaf/string.h>

#ifdef CPAF_WIN32
#   include <windows.h>
#   include <cstring>
#endif

cpaf::String::String(const String &c)
    : StringBase(c),
    m_encoding(c.m_encoding)
{ }

/*
    For platforms where strings are not stored internally as char's, this function
    first constructs an empty base object, converts to the native string type,
    and assigns to 'this'
*/
cpaf::String::String(const char *chars, char_encoding encoding)

#ifdef CPAF_WIN32
    : StringBase(cS("")),
#else
    : StringBase(chars),
#endif

    m_encoding(encoding)
{
#ifdef CPAF_WIN32
    // convert from char* to wchar_t*

    int len = strlen(chars);

    // don't need to do anything if the string was empty
    if( len == 0 )
        return;

    // if the encoding is not UTF8, use the CP_ACP code page
    // if it is, use CP_UTF8
    int code_page;
    if( encoding == UTF8 )
        code_page = CP_UTF8;
    else
        code_page = CP_ACP;

    // waste a little memory for efficiencies sake
    len *= 4;
    wchar_t *buff = new wchar_t[len]; // 4 times the length of the string will always be enough of a buffer

    // convert
    //! \todo throw if this function fails
    MultiByteToWideChar(code_page, 0, chars, -1, buff, len);
    
    // construct a new string object from our wide character buffer
    cpaf::String temp(buff);

    // assign the string to 'this' to complete construction
    *this = temp;

    delete buff;

#endif
}

cpaf::String::String(const wchar_t *chars, char_encoding encoding)

#ifdef CPAF_WIN32
    : StringBase(chars),
#else
    : StringBase(cS("")),
#endif
    m_encoding(encoding)
{
    //! \todo implement the conversion from wide char to native representation for non win32 ports
}

int cpaf::String::get_encoding()
{
    return m_encoding;
}

const cpaf::String &cpaf::String::convert(int encoding)
{
    if( encoding == m_encoding )
        // nothing to do;
        return *this;

    //!\todo implement me!
    return *this;
}

// we will need conditional compilation for this function
// win32 uses certain functions for the conversions
// *nix ports will use others
cpaf::String cpaf::String::get_encoding(int encoding)
{
    //! \todo implement me!
    return *this;
}
