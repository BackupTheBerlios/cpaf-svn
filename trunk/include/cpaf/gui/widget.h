/*!
    \file include/cpaf/gui/widget.h
    \brief cpaf::gui::Widget declaration
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

#ifndef CPAF_GUI_WIDGET_H
#define CPAF_GUI_WIDGET_H

#include <cpaf/gui/object.h>
#include <cpaf/gui/initializer/widget.h>

#include <map>

namespace cpaf {
    namespace gui {

class Panel;
class Window;
class LayoutManager;

/*!
    \brief Serves as the base class for all Widgets
*/
class CPAF_API Widget : public Object
{
public:
    typedef cpaf::api::gui::Widget api_type;

    /*!
        \return A native handle for the widget. This value is returned as a void*, and how you use this value
            is dependant on the port you are working with. For win32, simply casting the return value to a HWND
            is sufficient.
        \todo Casting a pointer type to a type that isn't a pointer may not work under all circumstances
    */
    void *get_handle() const;

    /*!
        \brief Enables or disables the widget. Disabled widgets cannot recieve user input.
    */
    void enable(bool e);
    void disable();

    /*!
        \brief Shows or hides a widget.
    */
    void show(bool show = true, bool focus = false);
    void hide();

    /*!
        This function determines whether or not the widget is enabled. If any of a widget's parents
        are disabled, the widget is considered disabled. If all of the parents are enabled and the widget
        is also enabled, it is not disabled.
    */
    bool is_enabled() const;

    /*!
        \return True if the widget is shown and none of its parents are hidden, false otherwise. A widget
        is shown if it would be drawn by the system. A widget may be completely obscured by another widget,
        but if the widget would otherwise be drawn, this function returns true.
    */
    bool is_shown() const;

    /*!
        \brief Destroys this widget freeing all resources.
    */
    void destroy();

    /*!
        \return The parent of this widget
    */
    boost::shared_ptr<Panel> get_parent() const;

    /*!
        \return The Window which contains this widget
    */
    boost::shared_ptr<Window> get_parent_window() const;

    /*!
        \return This objects unique identifier
    */
    object_id get_id() const;

    int m_id;

    api_type *m_impl;

protected:
    Widget(api_type *impl);

public:
    virtual ~Widget();
    api_type *get_impl() const;
};

/*!
    Adds an {ID, Widget} pair to the widget id map
*/
void associate_widget_id(cpaf::object_id id, boost::shared_ptr<Widget> ptr);

/*!
    Removed an {ID, Widget} pair from the id map
*/
void disassociate_widget_id(cpaf::object_id id);

/*!
    Retrieves a shared_ptr to the widget with the given id
*/
boost::shared_ptr<Widget> get_widget_from_id(cpaf::object_id id);

    } // gui
} // cpaf

#endif // CPAF_GUI_WIDGET_H
