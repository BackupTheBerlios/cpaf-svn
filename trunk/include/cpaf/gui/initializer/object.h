/*!
    \file include/cpaf/gui/initializer/object.h
    \brief Initializer classes for cpaf::gui::Object
    \date Created: 2005-05-07
*/

#ifndef CPAF_GUI_INITIALIZER_OBJECT_H
#define CPAF_GUI_INITIALIZER_OBJECT_H

#include <boost/shared_ptr.hpp>
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
    //! The minimum allowable size of the object
    cpaf::Size m_min_size;

    //! The maximum allowable size of the object. A size of (0,0) means there is no maximum
    cpaf::Size m_max_size;

    //! The natural size of the object
    cpaf::Size m_natural_size;

    //! If true, the value of m_size must be ignored, and an acceptible size
    //! must be chosen automatically.
    bool m_default_size;

    //! If true, the value of m_pos must be ignored and an acceptible position
    //! must be chosen automatically
    bool m_default_pos;

public:
    ObjectData();
    virtual ~ObjectData();

    void set_min_size(const cpaf::Size &s);
    cpaf::Size get_min_size() const;
    void set_max_size(const cpaf::Size &s);
    cpaf::Size get_max_size() const;
    void set_natural_size(const cpaf::Size &s);
    cpaf::Size get_natural_size() const;
};

/*!
    \brief Initializer class for Object creation.
*/
template<class T> class Object
{
public:
    typedef ObjectData data_type;

protected:
    boost::shared_ptr<data_type> m_data;

    Object(data_type *data)
        : m_data(data)
    { }

public:
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

    T &natural_size(const cpaf::Size &s)
    {
        m_data->set_natural_size(s);
        return dynamic_cast<T&>(*this);
    }

    cpaf::Size get_min_size() const { return m_data->get_min_size(); }
    cpaf::Size get_max_size() const { return m_data->get_max_size(); }
    cpaf::Size get_natural_size() const { return m_data->get_natural_size(); }

    virtual ~Object() { }

private:
    // non assignable
    Object<T> &operator= (const Object<T> &);
};

        } // initializer
    } // gui
} // cpaf

#endif // CPAF_GUI_INITIALIZER_OBJECT_H
