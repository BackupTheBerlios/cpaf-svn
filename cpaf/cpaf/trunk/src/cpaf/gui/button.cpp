/*
Wrapper for api::gui::button
*/

#include <cpaf/gui/button.h>
#include <cpaf/api/gui/button.h>
#include <cpaf/private/factory.h>

cpaf::gui::Button::Button(cpaf::gui::Widget *parent)
: Widget( cpaf::gui::factory::create_widget<cpaf::api::gui::Button>( (parent) ?
          (cpaf::api::gui::Widget*)*parent : (cpaf::api::gui::Widget*)0 ) ),
    m_impl( dynamic_cast<cpaf::api::gui::Button*>(Widget::m_impl) )
{ }

cpaf::gui::Button::Button(cpaf::api::gui::Button *p)
    : Widget(p),
    m_impl(p)
{ }

cpaf::gui::Button::operator cpaf::api::gui::Button *()
{
    return m_impl;
}

cpaf::gui::Button &cpaf::gui::Button::operator =(cpaf::gui::Button *btn)
{
    //! \todo I need to take ownership of this m_impl, meaning
    //! registering this wrpaper as owning it and unregister the first wrapper
    m_impl = btn->m_impl;
    return *this;
}

void cpaf::gui::Button::set_label(const std::string &label)
{
    m_impl->set_label(label);
}

std::string cpaf::gui::Button::get_label()
{
    return m_impl->get_label();
}


cpaf::gui::Button *cpaf::gui::factory::Button::create()
{
    return new cpaf::gui::Button( cpaf::gui::factory::create_widget<cpaf::api::gui::Button>(*m_parent) );
}