/*
Client wrapper for api::gui::Object
*/

#ifndef CPAF_GUI_OBJECT_H
#define CPAF_GUI_OBJECT_H

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/types.h>

namespace cpaf {
    namespace gui {

class CPAF_API Object
{
public:

protected:
    cpaf::api::gui::Object *m_impl;

    //Object(const cpaf::api::gui::ObjectPtr &p);
    Object(cpaf::api::gui::Object *p);

public:
    virtual ~Object();

    operator cpaf::api::gui::Object *();

    virtual void set_size(const cpaf::Size &s);
    virtual void set_min_size(const cpaf::Size &s);
    virtual void set_max_size(const cpaf::Size &s);
    virtual void set_position(const cpaf::Point &p);
    virtual cpaf::Size get_size();
    virtual cpaf::Size get_min_size();
    virtual cpaf::Size get_max_size();
    virtual cpaf::Point get_position();
};

        namespace factory {

template <typename T>
class ObjectFact
{
protected:
    cpaf::Size m_size, m_min_size, m_max_size;
    cpaf::Point m_pos;

public:
    T &size(const cpaf::Size &s)
    {
        m_size = s;
        return *dynamic_cast<T*>(this);
    }

    T &min_size(const cpaf::Size &s)
    {
        m_min_size = s;
        return *dynamic_cast<T*>(this);
    }

    T &max_size(const cpaf::Size &s)
    {
        m_max_size = s;
        return *dynamic_cast<T*>(this);
    }

    T &position(const cpaf::Point &p)
    {
        m_pos = p;
        return *dynamic_cast<T*>(this);
    }

    cpaf::Size get_min_size() { return m_min_size; }
    cpaf::Size get_max_size() { return m_max_size; }
    cpaf::Size get_size() { return m_size; }
    cpaf::Point get_pos() { return m_pos; }

    virtual ~ObjectFact() { }
};

        } // factory
    } // gui
} // cpaf

#endif // CPAF_GUI_OBJECT_H
