/*!
    \file src/cpaf/gui/initializer/object.cpp
    \brief cpaf::gui::Object initializer implementation
    \date Created: 2005-07-27
*/

#include <cpaf/gui/initializer/object.h>

cpaf::gui::initializer::ObjectData::ObjectData()
    : m_default_size(true),
    m_default_pos(true)
{ }

cpaf::gui::initializer::ObjectData::~ObjectData() { }

void cpaf::gui::initializer::ObjectData::set_size(const cpaf::Size &s)
{
    m_size = s;
    m_default_size = false;
}

cpaf::Size cpaf::gui::initializer::ObjectData::get_size() const
{
    return m_size;
}

void cpaf::gui::initializer::ObjectData::set_min_size(const cpaf::Size &s)
{
    m_min_size = s;
}

cpaf::Size cpaf::gui::initializer::ObjectData::get_min_size() const
{
    return m_min_size;
}

void cpaf::gui::initializer::ObjectData::set_max_size(const cpaf::Size &s)
{
    m_max_size = s;
}

cpaf::Size cpaf::gui::initializer::ObjectData::get_max_size() const
{
    return m_max_size;
}

void cpaf::gui::initializer::ObjectData::set_pos(const cpaf::Point &p)
{
    m_pos = p;
    m_default_pos = false;
}

cpaf::Point cpaf::gui::initializer::ObjectData::get_pos() const
{
    return m_pos;
}

bool cpaf::gui::initializer::ObjectData::use_default_pos() const
{
    return m_default_pos;
}

bool cpaf::gui::initializer::ObjectData::use_default_size() const
{
    return m_default_size;
}
