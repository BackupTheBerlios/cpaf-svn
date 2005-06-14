/*!
    \file include/cpaf/app.h
    \brief cpaf::App declaration
    \date Created: 2004-04-07
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

#if _MSC_VER
#   pragma warning(disable:4786 4251)
#endif

#include <cpaf/dllimpexp.h>
#include <cpaf/event/event.h>

#include <vector>
#include <string>

namespace cpaf {

class CPAF_API App
{
public:
    /*!
        Command line storage as a vector of strings
    */
    typedef std::vector<std::string> cmd_line;

private:
    cmd_line m_cmd;
    cpaf::event::Manager m_manager; // construct the singleton event manager class

public:
    //! \todo Should I make this not an inilined dtor?
    virtual ~App() { }

    virtual bool init() = 0;
    virtual int run() = 0;

    /*!
        \return Command line used to launch the application
    */
    const cmd_line &get_cmd_line();
    void set_cmd_line(const cmd_line &cmd);
};

/*!
    Returns a reference to the cpaf::App object that is running this application

    \internal Note that this is implemented in src/cpaf/main.cpp
*/
CPAF_API App &get_app();

/*!
    Convenience template to save casting the return value of get_app to your
    derived application type.
*/
template<typename T> T &get_app()
{
    return dynamic_cast<T&>(cpaf::get_app());
}

} // cpaf

#endif // CPAF_APP_H
