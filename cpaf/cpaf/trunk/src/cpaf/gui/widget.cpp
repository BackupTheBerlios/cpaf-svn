/*
Wrapper for api::gui::widget
*/

#include <cpaf/gui/widget.h>
#include <cpaf/api/gui/widget.h>

using namespace cpaf::api::gui;

cpaf::gui::Widget::Widget(const WidgetPtr &p)
    : Sizeable(p),
    m_impl(p)
{ }

// empty virtual dtor
cpaf::gui::Widget::~Widget() { }

int cpaf::gui::Widget::get_handle()
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

void cpaf::gui::Widget::show(bool s)
{
    m_impl->show(s);
}

void cpaf::gui::Widget::hide()
{
    m_impl->show(false);
}

bool cpaf::gui::Widget::is_enabled()
{
    return m_impl->is_enabled();
}

bool cpaf::gui::Widget::is_shown()
{
    return m_impl->is_shown();
}
