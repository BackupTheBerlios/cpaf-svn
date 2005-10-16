/*!
    \file include/cpaf/gui/toplevel.h
    \brief cpaf::gui::TopLevel declaration
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

#ifndef CPAF_GUI_TOPLEVEL_H
#define CPAF_GUI_TOPLEVEL_H

#include <cpaf/gui/widget.h>

#include <string>

namespace cpaf {
    namespace gui {

class CPAF_API TopLevel : public Widget
{
public:
    typedef cpaf::api::gui::TopLevel api_type;

    void show(bool show = true, bool focus = true);

    /*!
        \brief Sets the title of the widgets caption.
    */
    void set_title(const std::string &t);

    /*!
        \return The title of the widgets caption.
    */
    std::string get_title() const;

    /*!
        \brief Sets the client size of the widget.
    */
    void set_client_size(const cpaf::Size &s);

    /*!
        \return The client size of the widget.
    */
    cpaf::Size get_client_size() const;

    /*!
        \return The position of the client area of a widget relative to the top-left corner
        of the frame extents. If the widget is managing a menubar and/or toolbar,
        the position of the client area will be moved down to make room.
    */
    cpaf::Point get_client_position() const;

private:
    api_type *m_impl;

protected:
    TopLevel(api_type *impl);

public:
    ~TopLevel();
    api_type *get_impl() const;
};

    } // gui
} // cpaf

#endif // CPAF_GUI_TOPLEVEL_H
