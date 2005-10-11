/*!
    \file include/cpaf/app.h
    \brief cpaf::App declaration
    \date Created: 2004-04-07
*/

/*
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef CPAF_APP_H
#define CPAF_APP_H

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

    /*!
        Initialize the application.
    */
    virtual bool init() = 0;

    /*!
        Run the application.
    */
    virtual int run() = 0;

    /*!
        Quit the application.
    */
    virtual void quit() = 0;

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
