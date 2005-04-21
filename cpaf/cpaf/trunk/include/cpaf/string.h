/*
Definition file for cpaf::String
*/

/*
cpaf::String is a specialization of std::basic_string. cpaf::String::char_type
varies per port and is the native character storage mechanism for unicode on that
platform. Currently, this means that gtk uses unsiged chars for UTF-8, and win32
uses wchar_t.
*/

#ifndef CPAF_STRING_H
#define CPAF_STRING_H

#include <string>
#include <cpaf/dllimpexp.h>

/*!
    \def cS(s)
    Macro used to encapsulate string literals. It is not required, but
    it should be used for more efficient construction of strings from
    compile time string literals.
*/
#ifdef CPAF_WIN32
#   define cS(s)    L##s
#else
#   define cS(S)    s
#endif

#ifdef CPAF_WIN32
#   include <wchar.h> // for the correct win32 wchar_t definition
#   define cpaf_char_t  wchar_t
#   define CPAF_DEFAULT_ENCODING    UTF16
#endif

#ifdef CPAF_GTK
#   define cpaf_char_t  unsigned char
#   define CPAF_DEFAULT_ENCODING    UTF8
#endif

namespace cpaf {

typedef std::basic_string<cpaf_char_t> StringBase;

class CPAF_API String : public StringBase
{
public:

    // string character encoding enum
    // Once cpaf stabilizes
    // DO NOT change this enum EXCEPT by adding things to the BOTTOM
    enum char_encoding
    {
        UTF8,
        UTF16
    };

private:
    char_encoding m_encoding;

public:
    /*!
        Copy constructor

        \param s    String being copied
    */
    String(const String &s);

    /*!
        Constructor for use when you have an array of char's and need a string. You can optionally
        specify what encoding the string should assume the characters have.

        \note For construction a string out of a string literal, construction will be optimal if that
            literal is encased within the cS() macro, which will select the appropriate constructor
            for the current build target that doesn't require a conversion.

        \param chars    The character buffer
        \param encoding The encoding of the character buffer, and the final encoding that the constructed
                        string will use.
    */
    String(const char *chars, char_encoding encoding = UTF8);

    /*!
        Constructor for use when you have an array of wide characters and need a string. You can optionally
        specify what encoding the string should assume the characters have.

        \note For construction a string out of a string literal, construction will be optimal if that
            literal is encased within the cS() macro, which will select the appropriate constructor
            for the current build target that doesn't require a conversion.

        \param chars    The character buffer
        \param encoding The encoding of the character buffer, and the final encoding that the constructed
                        string will use.
    */
    String(const wchar_t *chars, char_encoding encoding = UTF16);

    /*!
        \return The encoding format for this string. Will be one of the values of the char_encoding enumeration
    */
    int get_encoding();

    /*!
        Converts this string into the specified encoding. If the string is already in this encoding,
        nothing happens.

        \return A const reference to 'this' for convenience.
    */
    const String &convert(int encoding);

    /*!
        This function requests a copy of this string in a particular encoding.
        \todo This function could use a better name
        \return A copy of this string in the requested encoding.
        \warning Even if the string is already in the requested encoding, a copy will be made
            and returned. It is inneficient to use this function in those cases.
    */
    String get_encoding(int encoding);
};

} // cpaf

#endif
