/*
Sizeable interface definition
*/

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

    virtual void set_size(cpaf::Size s) = 0;
    virtual void set_min_size(cpaf::Size s) = 0;
    virtual void set_max_size(cpaf::Size s) = 0;
    virtual void set_position(cpaf::Point p) = 0;
    virtual cpaf::Size get_size() = 0;
    virtual cpaf::Size get_min_size() = 0;
    virtual cpaf::Size get_max_size() = 0;
    virtual cpaf::Point get_position() = 0;

};

        } // gui
    } // api
} // cpaf
