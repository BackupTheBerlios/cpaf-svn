/*!
    \file include/cpaf/gui/window.h
    \brief cpaf::gui::Window declaration
    \date Created: 2005-04-05
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

#ifndef CPAF_GUI_WINDOW_H
#define CPAF_GUI_WINDOW_H

#include <cpaf/gui/toplevel.h>
#include <cpaf/gui/initializer/window.h>

namespace cpaf {
    namespace gui {

/*!
    \brief A Window is a top level widget which has a title bar and contains subwindows
*/
class CPAF_API Window : public TopLevel
{
public:
    typedef cpaf::api::gui::Window api_type;
    typedef WindowInitializer Initializer;

    /*!
        Creates a Window
    */
    static boost::shared_ptr<Window> create(const Initializer &initializer);

    /*!
        Sets the content panel for this window
    */
    void set_content_panel(boost::shared_ptr<cpaf::gui::Panel> p);

    /*!
        \return This window's content panel
    */
    boost::shared_ptr<cpaf::gui::Panel> get_content_panel() const;

private:
    api_type *m_impl;

protected:
    Window();
    Window(api_type *impl);

    /*!
        \brief Constructs the native widget using the given initialization data
    */
    boost::shared_ptr<Window> initialize(const Initializer &initializer);

public:
    api_type *get_impl() const;
};

    } // gui
} // cpaf



#endif // CPAF_GUI_WINDOW_H
