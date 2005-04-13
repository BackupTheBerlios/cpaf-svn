/*
Wrapper for api::gui::Object
*/

#include <cpaf/gui/object.h>
#include <cpaf/api/gui/object.h>

using namespace cpaf::api::gui;

cpaf::gui::Object::Object(cpaf::api::gui::Object *p)
    : m_impl(p)
{ }

cpaf::gui::Object::~Object() { }    

cpaf::gui::Object::operator cpaf::api::gui::Object *()
{
    return m_impl;
}

void cpaf::gui::Object::set_size(const cpaf::Size &s)
{
    m_impl->set_size(s);
}

void cpaf::gui::Object::set_min_size(const cpaf::Size &s)
{
    m_impl->set_min_size(s);
}

void cpaf::gui::Object::set_max_size(const cpaf::Size &s)
{
    m_impl->set_max_size(s);
}

void cpaf::gui::Object::set_position(const cpaf::Point &p)
{
    m_impl->set_position(p);
}

cpaf::Size cpaf::gui::Object::get_size()
{
    return m_impl->get_size();
}

cpaf::Size cpaf::gui::Object::get_min_size()
{
    return m_impl->get_min_size();
}

cpaf::Size cpaf::gui::Object::get_max_size()
{
    return m_impl->get_max_size();
}

cpaf::Point cpaf::gui::Object::get_position()
{
    return m_impl->get_position();
}
