/*
Wrapper for api::gui::TopLevel
*/

#include <cpaf/gui/toplevel.h>
#include <cpaf/api/gui/toplevel.h>

using namespace cpaf::api::gui;

cpaf::gui::TopLevel::TopLevel(const TopLevelPtr &p)
    : Widget(p),
    m_impl(p.get())
{ }

void cpaf::gui::TopLevel::set_title(const std::string &t)
{
    m_impl->set_title(t);
}

std::string cpaf::gui::TopLevel::get_title()
{
    //return m_impl->get_title();
    return std::string("foo");
}
