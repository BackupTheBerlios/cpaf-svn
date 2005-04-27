/*
Client wrapper for api::gui::Widget
this object is not createable by client code
*/

#ifndef CPAF_GUI_WIDGET_H
#define CPAF_GUI_WIDGET_H

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/gui/object.h>

namespace cpaf {
    namespace gui {

        class App;

class CPAF_API Widget : public Object
{
protected:
    cpaf::api::gui::Widget *m_impl;

    //Widget(const cpaf::api::gui::WidgetPtr &p);
    Widget(cpaf::api::gui::Widget *p);

public:
    virtual ~Widget();

    operator cpaf::api::gui::Widget *();

    virtual void *get_handle();
    virtual void enable(bool e);
    virtual void disable();
    virtual void show(bool show = true, bool focus = false);
    virtual void hide();
    virtual bool is_enabled();
    virtual bool is_shown();
    int get_id();

};

        namespace factory {

template <typename T>
class WidgetFact : public ObjectFact<T>
{
protected:
    cpaf::gui::Widget *m_parent;
    bool m_show, m_enable;

public:
    WidgetFact()
        : m_parent(NULL),
        m_show(false),
        m_enable(true)
    { }

    T &parent(cpaf::gui::Widget *p)
    {
        m_parent = p;
        return *dynamic_cast<T*>(this);
    }

    T &show(bool s = true)
    {
        m_show = s;
        return *dynamic_cast<T*>(this);
    }

    T &hide()
    {
        m_show = false;
        return *dynamic_cast<T*>(this);
    }

    T &enable(bool s = true)
    {
        m_enable = s;
        return *dynamic_cast<T*>(this);
    }

    T &disable()
    {
        m_enable = false;
        return *dynamic_cast<T*>(this);
    }

    cpaf::gui::Widget *get_parent() { return m_parent; }
    bool get_show() { return m_show; }
    bool get_enable() { return m_enable; }
};

        } // factory
    } // gui
} // cpaf

#endif // CPAF_GUI_WIDGET_H
