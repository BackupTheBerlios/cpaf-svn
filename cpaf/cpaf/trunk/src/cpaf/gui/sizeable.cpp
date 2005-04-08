/*
Wrapper for api::gui::Sizeable
*/

#include <cpaf/gui/sizeable.h>
#include <cpaf/api/gui/sizeable.h>

using namespace cpaf::api::gui;

cpaf::gui::Sizeable::Sizeable(const SizeablePtr &p)
    : m_impl(p)
{ }

// empty virtual dtor
cpaf::gui::Sizeable::~Sizeable() { }

void cpaf::gui::Sizeable::set_size(const cpaf::Size &s)
{
    m_impl->set_size(s);
}

void cpaf::gui::Sizeable::set_min_size(const cpaf::Size &s)
{
    m_impl->set_min_size(s);
}

void cpaf::gui::Sizeable::set_max_size(const cpaf::Size &s)
{
    m_impl->set_max_size(s);
}

void cpaf::gui::Sizeable::set_position(const cpaf::Point &p)
{
    m_impl->set_position(p);
}

cpaf::Size cpaf::gui::Sizeable::get_size()
{
    return m_impl->get_size();
}

cpaf::Size cpaf::gui::Sizeable::get_min_size()
{
    return m_impl->get_min_size();
}

cpaf::Size cpaf::gui::Sizeable::get_max_size()
{
    return m_impl->get_max_size();
}

cpaf::Point cpaf::gui::Sizeable::get_position()
{
    return m_impl->get_position();
}
