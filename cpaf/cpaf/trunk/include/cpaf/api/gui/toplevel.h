/*
TopLevel interface definition
*/

#include <cpaf/api/gui/widget.h>

#include <string>

namespace cpaf {
    namespace api {
        namespace gui {

/*!
    \brief The TopLevel interface defines a widget that is a top level widget.
*/
class TopLevel : public Widget
{
public:

    /*!
        \brief Sets the title of the widgets caption.
    */
    virtual void set_title(const std::string &t) = 0;

    /*!
        \return The title of the widgets caption.
    */
    virtual std::string get_title() = 0;

    /*
    virtual void maximize() = 0;
    virtual void minimize() = 0;
    */

    /*!
        \brief Sets the client size of the widget.
    */
    virtual void set_client_size(cpaf::Size s) = 0;

    /*!
        \return The client size of the widget.
    */
    virtual cpaf::Size get_client_size() = 0;

    /*!
        \return The position of the client area of a widget relative to the top-left corner
        of the frame extents. If the widget is managing a menubar and/or toolbar,
        the position of the client area will be moved down to make room.
    */
    virtual cpaf::Point get_client_position() = 0;

};

        } // gui
    } // api
} // cpaf
