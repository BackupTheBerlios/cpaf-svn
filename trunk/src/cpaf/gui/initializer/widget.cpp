/*!
    \file src/cpaf/gui/initializer/widget.cpp
    \brief cpaf::gui::Widget initializer implementation
    \date Created: 2005-07-27
*/

#include <cpaf/gui/initializer/widget.h>

cpaf::gui::initializer::WidgetData::WidgetData()
    : m_wrapper(NULL),
    m_parent(NULL),
    m_show(false),
    m_activate(false),
    m_enable(true)
{ }

void cpaf::gui::initializer::WidgetData::set_wrapper(cpaf::gui::Widget *w)
{
    m_wrapper = w;
}

cpaf::gui::Widget *cpaf::gui::initializer::WidgetData::get_wrapper() const
{
    return m_wrapper;
}

void cpaf::gui::initializer::WidgetData::set_parent(cpaf::gui::Panel *p)
{
    m_parent = p;
}

cpaf::gui::Panel *cpaf::gui::initializer::WidgetData::get_parent() const
{
    return m_parent;
}

void cpaf::gui::initializer::WidgetData::set_show(bool b)
{
    m_show = b;
}

bool cpaf::gui::initializer::WidgetData::get_show() const
{
    return m_show;
}

void cpaf::gui::initializer::WidgetData::set_activate(bool b)
{
    m_activate = b;
}

bool cpaf::gui::initializer::WidgetData::get_activate() const
{
    return m_activate;
}

void cpaf::gui::initializer::WidgetData::set_enable(bool b)
{
    m_enable = b;
}

bool cpaf::gui::initializer::WidgetData::get_enable() const
{
    return m_enable;
}
