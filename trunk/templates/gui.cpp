/*!
    \file src/cpaf/gui/$(NAME_LOWER).$(SRC_EXT)
    \brief Implementation of cpaf::gui::$(NAME)
    \date Created: $(DATE)
*/

#include <cpaf/gui/$(NAME_LOWER).h>
#include <cpaf/api/gui/$(NAME_LOWER).h>
#include <cpaf/private/factory.h>

cpaf::gui::$(NAME)::$(NAME)()
    : $(BASE)(cpaf::gui::factory::create_widget_implementation<api_type>())
{
    m_impl = get_impl<api_type>();
}

cpaf::gui::$(NAME)::$(NAME)(api_type *impl)
    : $(BASE)(impl),
    m_impl(impl)
{ }

void cpaf::gui::$(NAME)::create(const Initializer &initializer)
{
    Initializer::data_type params = initializer.get_data();
    params.set_wrapper(this);
    m_impl->create(params);
}

cpaf::gui::$(NAME)::operator api_type *() const
{
    return m_impl;
}
