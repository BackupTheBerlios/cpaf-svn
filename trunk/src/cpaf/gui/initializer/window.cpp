/*!
    \file src/cpaf/gui/initializer/window.cpp
    \brief cpaf::gui::Window initializer implementation
    \date Created: 2005-07-27
*/

#include <cpaf/gui/initializer/window.h>

using namespace cpaf::gui::initializer;

WindowData::WindowData()
    : m_use_client_size(false),
    m_content_panel(0)
{
    // windows should be activated when shown by default
    WidgetData::m_activate = true;
}

void WindowData::set_title(const std::string &str)
{
    m_title = str;
}

std::string WindowData::get_title() const
{
    return m_title;
}

void WindowData::set_client_size(const cpaf::Size &s)
{
    m_client_size = s;
    m_default_size = false;
    m_use_client_size = true;
}

cpaf::Size WindowData::get_client_size() const
{
    return m_client_size;
}

bool WindowData::use_client_size() const
{
    return m_use_client_size;
}

void WindowData::set_content_panel(cpaf::gui::Panel *p)
{
    m_content_panel = p;
}

cpaf::gui::Panel *WindowData::get_content_panel() const
{
    return m_content_panel;
}

cpaf::gui::WindowInitializer::WindowInitializer()
    : cpaf::gui::initializer::Window<WindowInitializer>(new data_type)
{ }

cpaf::gui::WindowInitializer::data_type cpaf::gui::WindowInitializer::get_data() const
{
    return *m_data;
}
