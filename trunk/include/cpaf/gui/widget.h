/*!
    \file include/cpaf/gui/widget.h
    \brief cpaf::gui::Widget declaration
    \date Created: 2005-04-05
*/

#ifndef CPAF_GUI_WIDGET_H
#define CPAF_GUI_WIDGET_H

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/types.h>

//#include <cpaf/gui/object.h>
#include <cpaf/gui/initializer/widget.h>

namespace cpaf {
    namespace gui {

/*!
    \brief Serves as the base class for all Widgets
*/
class CPAF_API Widget
{
public:
    typedef cpaf::api::gui::Widget api_type;

    /*!
        \brief Sets the absolute size of a widget.
    */
    void set_size(const cpaf::Size &s);

    /*!
        \brief Sets the minimum size of the widget. A value of -1 for width or height
        indicates that there is no minimum size in that direction.
    */
    void set_min_size(const cpaf::Size &s);

    /*!
        \brief Sets the maximum size of the widget. A value of -1 for width or height
        indicates that there is no maximum size in that direction.
    */
    void set_max_size(const cpaf::Size &s);

    /*!
        \brief Sets the position of a widget. If the widget is a \ref g_tlw TLW, the position is in
        screen coordinates. Otherwise, the position is in client coordinates.
    */
    void set_position(const cpaf::Point &p);

    /*!
        \return Absolute size of the widget
    */
    cpaf::Size get_size();

    /*!
        \return Minimum size of the widget. A value of -1 for width or height
        indicates that there is no minimum size in that direction.
    */
    cpaf::Size get_min_size();

    /*!
        \return Maximum size of the widget. A value of -1 for width or height
        indicates that there is no maximum size in that direction.
    */
    cpaf::Size get_max_size();

    /*!
        \return Position of the widget. If the widget is a \ref g_tlw TLW, the position is in
        screen coordinates. Otherwise, the position is in client coordinates.
    */
    cpaf::Point get_position();

    /*!
        \return A native handle for the widget. This value is returned as a void*, and how you use this value
            is dependant on the port you are working with. For win32, simply casting the return value to a HWND
            is sufficient.
    */
    void *get_handle();

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
    bool is_enabled();

    /*!
        \return True if the widget is shown and none of its parents are hidden, false otherwise. A widget
        is shown if it would be drawn by the system. A widget may be completely obscured by another widget,
        but if the widget would otherwise be drawn, this function returns true.
    */
    bool is_shown();

    /*!
        \brief Destroys this widget freeing all resources.
    */
    void destroy();

    /*!
        \return This objects unique identifier
    */
    object_id get_id();

    virtual ~Widget();

private:
    int m_id;

    api_type *m_impl;

protected:
    Widget(api_type *impl);

    template<typename T> T *get_impl()
    {
        return dynamic_cast<T*>(m_impl);
    }

public:
    operator api_type *();
};

    } // gui
} // cpaf

#endif // CPAF_GUI_WIDGET_H
