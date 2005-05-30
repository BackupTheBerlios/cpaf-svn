/*
Object initializer factory
*/

#ifndef CPAF_GUI_FACTORY_OBJECT_H
#define CPAF_GUI_FACTORY_OBJECT_H

#include <memory> // for std::auto_ptr

namespace cpaf {
    namespace gui {
        namespace factory {

class ObjectData
{
public:
    cpaf::Size m_size, m_min_size, m_max_size;
    cpaf::Point m_pos;

    virtual ~ObjectData() { }
};

template<class T> class Object
{
protected:
    std::auto_ptr<ObjectData> m_data;

    Object(ObjectData *data)
        : m_data(data)
    { }

public:
    T &size(const cpaf::Size &s)
    {
        m_data->m_size = s;
        return *dynamic_cast<T*>(this);
    }

    T &min_size(const cpaf::Size &s)
    {
        m_data->m_min_size = s;
        return *dynamic_cast<T*>(this);
    }

    T &max_size(const cpaf::Size &s)
    {
        m_data->m_max_size = s;
        return *dynamic_cast<T*>(this);
    }

    T &position(const cpaf::Point &p)
    {
        m_data->m_pos = p;
        return *dynamic_cast<T*>(this);
    }

    cpaf::Size get_min_size() const { return m_data->m_min_size; }
    cpaf::Size get_max_size() const { return m_data->m_max_size; }
    cpaf::Size get_size() const { return m_data->m_size; }
    cpaf::Point get_pos() const { return m_data->m_pos; }

    virtual ~Object() { }
};

        } // factory
    } // gui
} // cpaf

#endif
