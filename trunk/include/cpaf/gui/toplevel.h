/*!
    \file include/cpaf/gui/toplevel.h
    \brief cpaf::gui::TopLevel declaration
    \date Created: 2005-04-05
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
    operator api_type *() const;
};

    } // gui
} // cpaf

#endif // CPAF_GUI_TOPLEVEL_H
