/*!
    \file incude/cpaf/debug.h
    \brief Stream like object for outputting debug information
    \date Created: 2005-08-20
*/

#ifndef CPAF_DEBUG_H
#define CPAF_DEBUG_H

#include <iostream>
#include <sstream>

// userful headers for output manipulation
#include <iomanip>

#ifdef _MSC_VER
#include <crtdbg.h>
#endif

// windows headers are anoying and #define ERROR so get rid of it if needed
#ifdef ERROR
#undef ERROR
#endif

namespace cpaf {

/*!
    \brief Used like std::cout to print debug messages. When building with Visual Studio,
    debug messages will be printed to the Visual Studio debugger window. Otherwise,
    std::cout is used.

    Output is cached. To flush the cache, use std::endl. The cache is also flushed
    upon object destruction. The act of flushing a cache will output the debug messages
    and append a newline. Using std::endl will not append a second newline. You do
    not need to add a newline yourself unless you want a blank line inbetween debug
    messasges.

    Different types of debug reports will go to different places. When compiling with Visual Studio,
    all messages will go to the debug window, but messages of type ERROR will spawn a run time debug
    information window with options to ignore the error, terminate execution, or break. For other
    platforms, messages of type ERROR will be output to std::cerr while MESSAGEs will go to std::cout.
*/
class DebugReport
{
public:
    enum REPORT_TYPE {
        MESSAGE,
        ERROR
    };

    DebugReport(REPORT_TYPE report_type = MESSAGE, const char *file = 0, int line = 0, const char *module = 0)
#ifdef _DEBUG
        : m_type(report_type), m_file(file), m_line(line), m_module(module)
#endif
    { }

#ifdef _DEBUG
    ~DebugReport() { flush(); }
#endif

    /*!
        Print an element to the stream
    */
    
    template<typename T> friend const DebugReport &operator << (const DebugReport &r, const T &t)
    {
#ifdef _DEBUG
        r.m_ss << t;
#endif
        return r;
    }

    /*!
        Used to print simple output manipulator objects (std::hex, etc) to the stream
    */
    friend const DebugReport &operator << (const DebugReport &r, std::ios_base& (*func)(std::ios_base&))
    {
#ifdef _DEBUG
        r.m_ss << func;
#endif
        return r;
    }

    /*!
        Flushes the stream
    */
    friend const DebugReport &operator << (const DebugReport &r, std::basic_ostream<char, std::char_traits<char> >& (*func)(std::basic_ostream<char, std::char_traits<char> >&) )
    {
#ifdef _DEBUG
        r.flush();
#endif
        return r;
    }

    /*!
        Flushes the stream (Wide character std::endl version)
    */
    friend const DebugReport &operator << (const DebugReport &r, std::basic_ostream<wchar_t, std::char_traits<wchar_t> >& (*func)(std::basic_ostream<wchar_t, std::char_traits<wchar_t> >&) )
    {
#ifdef _DEBUG
        r.flush();
#endif
        return r;
    }

#ifdef _DEBUG
private:
    mutable std::stringstream m_ss;
    int m_type, m_line;
    const char *m_file, *m_module;

    /*!
        For non visual studio builds, this returns an appropriate ostream
    */
    std::ostream &get_ostream() const
    {
        switch(m_type)
        {
        case MESSAGE:
            return std::cout;
        case ERROR:
            return std::cerr;
        default:
            return std::cout;
        }
    }

    /*!
        Outputs the contents of the buffer to the VS debugger
    */
    void flush() const
    {
        if( !m_ss.str().empty() )
        {

#ifdef _MSC_VER // Visual Studio debug output

            int type;
            switch(m_type)
            {
            case MESSAGE:
                type = _CRT_WARN;
                break;
            case ERROR:
                type = _CRT_ERROR;
                break;
            default:
                type = _CRT_WARN;
            }

            // if _CRT_ERROR is used and "Retry" is selected, break
            if( ::_CrtDbgReport(type, m_file, m_line, m_module, "%s\n", m_ss.str().c_str()) == 1 )
                ::_CrtDbgBreak();

#else // !_MSC_VER Debug output for other compilers

            std::ostream &out = get_ostream();

            if( m_file )
            {
                if( m_line )
                    out << m_file << "(" << m_line << ")";
                else
                    out << m_file;
                out << ": ";
            }

            out << m_ss.str() << "\n";

#endif // _MSC_VER

            m_ss.str("");
        }
    }
#endif // _DEBUG
public:
    DebugReport(const DebugReport&) { }
};

} // cpaf

#endif // CPAF_DEBUG_H
