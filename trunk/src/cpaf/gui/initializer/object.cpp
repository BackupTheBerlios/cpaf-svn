/*!
    \file src/cpaf/gui/initializer/object.cpp
    \brief cpaf::gui::Object initializer implementation
    \date Created: 2005-07-27
*/

#include <cpaf/gui/initializer/object.h>

using namespace cpaf::gui::initializer;

ObjectData::ObjectData()
    : m_default_size(true),
    m_default_pos(true)
{ }

ObjectData::~ObjectData() { }

void ObjectData::set_size(const cpaf::Size &s)
{
    m_size = s;
    m_default_size = false;
}

cpaf::Size ObjectData::get_size() const
{
    return m_size;
}

void ObjectData::set_min_size(const cpaf::Size &s)
{
    m_min_size = s;
}

cpaf::Size ObjectData::get_min_size() const
{
    return m_min_size;
}

void ObjectData::set_max_size(const cpaf::Size &s)
{
    m_max_size = s;
}

cpaf::Size ObjectData::get_max_size() const
{
    return m_max_size;
}

void ObjectData::set_pos(const cpaf::Point &p)
{
    m_pos = p;
    m_default_pos = false;
}

cpaf::Point ObjectData::get_pos() const
{
    return m_pos;
}

bool ObjectData::use_default_pos() const
{
    return m_default_pos;
}

bool ObjectData::use_default_size() const
{
    return m_default_size;
}
