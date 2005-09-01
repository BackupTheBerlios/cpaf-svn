/*!
    \file src\cpaf\layout_manager.h
    \brief Layout Manager declarations
    \date Created: 2005-08-24
*/

#ifndef CPAF_GUI_LAYOUTMANAGER_H
#define CPAF_GUI_LAYOUTMANAGER_H

#include <cpaf/dllimpexp.h>
#include <cpaf/types.h>

namespace cpaf{
    namespace gui {

        class Widget;

/*!
    Base class for layout managers
    \todo pimpl
*/
class CPAF_API LayoutManager
{
public:
    /*!
        Updates the position and size of all managed widgets
    */
    virtual void do_layout(const cpaf::Size &size) = 0;

protected:
    /*!
        Sets the position for a given widget
    */
    void set_widget_pos(Widget *widget, const cpaf::Point &pos);

    /*!
        Sets the size for a given widget
    */
    void set_widget_size(Widget *widget, const cpaf::Size &size);

    /*!
        Sets the rect for a given widget
    */
    void set_widget_rect(Widget *widget, const cpaf::Rect &rect);

public:
    virtual ~LayoutManager();
};

    } // gui
} // cpaf

#endif
