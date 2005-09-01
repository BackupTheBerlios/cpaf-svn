/*!
    \file include/cpaf/gui/api/object.h
    \brief Object interface declaration
    \date Created: 2005-04-05
*/

#ifndef CPAF_API_GUI_OBJECT_H
#define CPAF_API_GUI_OBJECT_H

#include <cpaf/gui/initializer/object.h>
#include <cpaf/types.h>

namespace cpaf {
    namespace api {
        namespace gui {

/*!
    \brief The Object interface represents an object that can be positioned and sized. It does
        not neccesarily represent a widget which has a presence at the system level.
*/
class Object
{
public:
    typedef cpaf::gui::initializer::ObjectData data_Type; //!< initialization data used for Objects

    // virtual dtor ensuring that all gui objects are properly destructed
    virtual ~Object();
    virtual void set_size(const cpaf::Size&) = 0;
    virtual void set_min_size(const cpaf::Size&) = 0;
    virtual void set_max_size(const cpaf::Size&) = 0;
    virtual void set_position(const cpaf::Point&) = 0;
    virtual void set_rect(const cpaf::Rect&) = 0;
    virtual cpaf::Size get_size() const = 0;
    virtual cpaf::Size get_min_size() const = 0;
    virtual cpaf::Size get_max_size() const = 0;
    virtual cpaf::Point get_position() const = 0;
    virtual cpaf::Rect get_rect() const = 0;

};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_OBJECT_H
