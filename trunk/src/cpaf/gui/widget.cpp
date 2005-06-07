/*!
    \file src/cpaf/gui/widget.cpp
    \brief Implementation of cpaf::gui::Widget
    \date Created: 2005-04-05
*/

#include <cpaf/gui/widget.h>
#include <cpaf/api/gui/widget.h>

// for delete_widget_implementation
#include <cpaf/private/factory.h>

using namespace cpaf::api::gui;

cpaf::gui::Widget::Widget()
    : m_id(cpaf::gui::factory::get_unique_object_id()),
    m_impl(NULL)
{ }

void cpaf::gui::Widget::set_impl(cpaf::api::gui::Widget *impl)
{
    m_impl = impl;

    // add the wrapper / implementation pair to the map
    //cpaf::gui::factory::add_implementation_wrapper(m_impl, this);
}

cpaf::gui::Widget::~Widget()
{
    // delete the implementation safely
    //cpaf::gui::factory::delete_widget_implementation(m_impl);
}

void cpaf::gui::Widget::destroy()
{
    // delete our implementation, which in turn deletes 'this'.
    delete m_impl;
}

cpaf::gui::Widget::operator cpaf::api::gui::Widget *()
{
    return m_impl;
}

void cpaf::gui::Widget::set_size(const cpaf::Size &s)
{
    m_impl->set_size(s);
}

void cpaf::gui::Widget::set_min_size(const cpaf::Size &s)
{
    m_impl->set_min_size(s);
}

void cpaf::gui::Widget::set_max_size(const cpaf::Size &s)
{
    m_impl->set_max_size(s);
}

void cpaf::gui::Widget::set_position(const cpaf::Point &p)
{
    m_impl->set_position(p);
}

cpaf::Size cpaf::gui::Widget::get_size()
{
    return m_impl->get_size();
}

cpaf::Size cpaf::gui::Widget::get_min_size()
{
    return m_impl->get_min_size();
}

cpaf::Size cpaf::gui::Widget::get_max_size()
{
    return m_impl->get_max_size();
}

cpaf::Point cpaf::gui::Widget::get_position()
{
    return m_impl->get_position();
}

void *cpaf::gui::Widget::get_handle()
{
    return m_impl->get_handle();
}

void cpaf::gui::Widget::enable(bool e)
{
    m_impl->enable(e);
}

void cpaf::gui::Widget::disable()
{
    m_impl->enable(false);
}

void cpaf::gui::Widget::show(bool show, bool activate)
{
    m_impl->show(show, activate);
}

void cpaf::gui::Widget::hide()
{
    m_impl->show(false, false);
}

bool cpaf::gui::Widget::is_enabled()
{
    return m_impl->is_enabled();
}

bool cpaf::gui::Widget::is_shown()
{
    return m_impl->is_shown();
}

int cpaf::gui::Widget::get_id()
{
    return m_id;
}
