/*!
    \file src/cpaf/gui/initializer/window.cpp
    \brief cpaf::gui::Window initializer implementation
    \date Created: 2005-07-27
*/

#include <cpaf/gui/initializer/window.h>

cpaf::gui::initializer::WindowData::WindowData()
    : m_use_client_size(false)
{
    // windows should be activated when shown by default
    WidgetData::m_activate = true;
}

void cpaf::gui::initializer::WindowData::set_title(const std::string &str)
{
    m_title = str;
}

std::string cpaf::gui::initializer::WindowData::get_title() const
{
    return m_title;
}

void cpaf::gui::initializer::WindowData::set_client_size(const cpaf::Size &s)
{
    m_client_size = s;
    m_default_size = false;
    m_use_client_size = true;
}

cpaf::Size cpaf::gui::initializer::WindowData::get_client_size() const
{
    return m_client_size;
}

bool cpaf::gui::initializer::WindowData::use_client_size() const
{
    return m_use_client_size;
}

cpaf::gui::WindowInitializer::WindowInitializer()
    : cpaf::gui::initializer::Window<WindowInitializer>(new data_type)
{ }

cpaf::gui::WindowInitializer::data_type cpaf::gui::WindowInitializer::get_data() const
{
    return *m_data;
}
