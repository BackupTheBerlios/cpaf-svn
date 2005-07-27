/*!
    \file include/cpaf/gui/initializer/object.h
    \brief Initializer classes for cpaf::gui::Object
    \date Created: 2005-05-07
*/

#ifndef CPAF_GUI_INITIALIZER_OBJECT_H
#define CPAF_GUI_INITIALIZER_OBJECT_H

#include <memory> // for std::auto_ptr
#include <cpaf/dllimpexp.h>
#include <cpaf/types.h>

namespace cpaf {
    namespace gui {
        namespace initializer {

/*!
    \brief Initializer data for Object creation.
*/
struct CPAF_API ObjectData
{
protected:
    //! \todo We need a special value to indicate "no maximum size." -1?

    //! The size of the object
    cpaf::Size m_size;

    //! The minimum allowable size of the object
    cpaf::Size m_min_size;

    //! The maximum allowable size of the object. A size of (0,0) means there is no maximum
    cpaf::Size m_max_size;

    //! The position of the object
    cpaf::Point m_pos;

    //! If true, the value of m_size must be ignored, and an acceptible size
    //! must be chosen automatically.
    bool m_default_size;

    //! If true, the value of m_pos must be ignored and an acceptible position
    //! must be chosen automatically
    bool m_default_pos;

public:
    ObjectData();
    virtual ~ObjectData();

    void set_size(const cpaf::Size &s);
    cpaf::Size get_size() const;
    void set_min_size(const cpaf::Size &s);
    cpaf::Size get_min_size() const;
    void set_max_size(const cpaf::Size &s);
    cpaf::Size get_max_size() const;
    void set_pos(const cpaf::Point &p);
    cpaf::Point get_pos() const;

    bool use_default_pos() const;
    bool use_default_size() const;
};

/*!
    \brief Initializer class for Object creation.
*/
template<class T> class Object
{
public:
    typedef ObjectData data_type;

protected:
    std::auto_ptr<data_type> m_data;

    Object(data_type *data)
        : m_data(data)
    { }

public:
    T &size(const cpaf::Size &s)
    {
        m_data->set_size(s);
        return dynamic_cast<T&>(*this);
    }

    T &min_size(const cpaf::Size &s)
    {
        m_data->set_min_size(s);
        return dynamic_cast<T&>(*this);
    }

    T &max_size(const cpaf::Size &s)
    {
        m_data->set_max_size(s);
        return dynamic_cast<T&>(*this);
    }

    T &position(const cpaf::Point &p)
    {
        m_data->set_pos(p);
        return dynamic_cast<T&>(*this);
    }

    cpaf::Size get_min_size() const { return m_data->get_min_size(); }
    cpaf::Size get_max_size() const { return m_data->get_max_size(); }
    cpaf::Size get_size() const { return m_data->get_size(); }
    cpaf::Point get_pos() const { return m_data->get_pos(); }

    virtual ~Object() { }

    // non copyable and non assignable
private:
    Object(const Object<T> &) { }
    Object<T> &operator= (const Object<T> &) { return *this; }
};

        } // initializer
    } // gui
} // cpaf

#endif // CPAF_GUI_INITIALIZER_OBJECT_H
