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

void ObjectData::set_natural_size(const cpaf::Size &s)
{
    m_natural_size = s;
}

cpaf::Size ObjectData::get_natural_size() const
{
    return m_natural_size;
}
