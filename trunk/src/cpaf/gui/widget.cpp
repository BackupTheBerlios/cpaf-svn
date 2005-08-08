/*!
    \file src/cpaf/gui/widget.cpp
    \brief Implementation of cpaf::gui::Widget
    \date Created: 2005-04-05
*/

#include <cpaf/gui/widget.h>
#include <cpaf/api/gui/widget.h>

// for delete_widget_implementation
#include <cpaf/private/factory.h>

using cpaf::object_id;

cpaf::gui::Widget::Widget(api_type *impl)
    : m_id(cpaf::gui::factory::get_unique_object_id()),
    m_impl(impl)
{
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
    m_impl->destroy();
}

cpaf::gui::Widget::api_type *cpaf::gui::Widget::get_impl() const
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

cpaf::Size cpaf::gui::Widget::get_size() const
{
    return m_impl->get_size();
}

cpaf::Size cpaf::gui::Widget::get_min_size() const
{
    return m_impl->get_min_size();
}

cpaf::Size cpaf::gui::Widget::get_max_size() const
{
    return m_impl->get_max_size();
}

cpaf::Point cpaf::gui::Widget::get_position() const
{
    return m_impl->get_position();
}

void *cpaf::gui::Widget::get_handle() const
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

bool cpaf::gui::Widget::is_enabled() const
{
    return m_impl->is_enabled();
}

bool cpaf::gui::Widget::is_shown() const
{
    return m_impl->is_shown();
}

object_id cpaf::gui::Widget::get_id() const
{
    return m_id;
}

cpaf::gui::Panel *cpaf::gui::Widget::get_parent() const
{
    return m_impl->get_parent();
}

cpaf::gui::Window *cpaf::gui::Widget::get_parent_window() const
{
    return m_impl->get_parent_window();
}
