/*
Sizeable interface definition
*/

#ifndef CPAF_API_GUI_SIZEABLE_H
#define CPAF_API_GUI_SIZEABLE_H

namespace cpaf {

    struct Size;
    struct Point;

    namespace api {
        namespace gui {

/*!
    \brief The Sizeable interface represents an object that can be positioned and sized.
*/
class Sizeable
{
public:

    /*!
        \brief Sets the absolute size of a widget.
    */
    virtual void set_size(const cpaf::Size &s) = 0;

    /*!
        \brief Sets the minimum size of the widget. A value of -1 for width or height
        indicates that there is no minimum size in that direction.
    */
    virtual void set_min_size(const cpaf::Size &s) = 0;

    /*!
        \brief Sets the maximum size of the widget. A value of -1 for width or height
        indicates that there is no maximum size in that direction.
    */
    virtual void set_max_size(const cpaf::Size &s) = 0;

    /*!
        \brief Sets the position of a widget. If the widget is a \ref g_tlw TLW, the position is in
        screen coordinates. Otherwise, the position is in client coordinates.
    */
    virtual void set_position(const cpaf::Point &p) = 0;

    /*!
        \return Absolute size of the widget
    */
    virtual cpaf::Size get_size() = 0;

    /*!
        \return Minimum size of the widget. A value of -1 for width or height
        indicates that there is no minimum size in that direction.
    */
    virtual cpaf::Size get_min_size() = 0;

    /*!
        \return Maximum size of the widget. A value of -1 for width or height
        indicates that there is no maximum size in that direction.
    */
    virtual cpaf::Size get_max_size() = 0;

    /*!
        \return Position of the widget. If the widget is a \ref g_tlw TLW, the position is in
        screen coordinates. Otherwise, the position is in client coordinates.
    */
    virtual cpaf::Point get_position() = 0;

};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_SIZEABLE_H
