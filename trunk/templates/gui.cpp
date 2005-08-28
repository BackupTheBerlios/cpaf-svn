/*!
    \file src/cpaf/gui/$(NAME_LOWER).$(SRC_EXT)
    \brief Implementation of cpaf::gui::$(NAME)
    \date Created: $(DATE)
*/

#include <cpaf/gui/$(NAME_LOWER).h>
#include <cpaf/api/gui/$(NAME_LOWER).h>
#include <cpaf/private/factory.h>

$(IF CONSTRUCTABLE)
cpaf::gui::$(NAME)::$(NAME)()
    : $(BASE)(cpaf::gui::factory::create_widget_implementation<api_type>())
{
    m_impl = cpaf::gui::Widget::get_impl<api_type>();
}
$(END)

cpaf::gui::$(NAME)::$(NAME)(api_type *impl)
    : $(BASE)(impl),
    m_impl(impl)
{ }

$(IF CONSTRUCTABLE)
$(NAME) *$(NAME)::create(const Initializer &initializer)
{
    $(NAME) *wrapper = new $(NAME);
    wrapper->initialize(initializer);
    return wrapper;
}

void cpaf::gui::$(NAME)::inintialize(const Initializer &initializer)
{
    Initializer::data_type params = initializer.get_data();
    params.set_wrapper(this);
    m_impl->create(params);
}
$(END)

cpaf::gui::$(NAME)::api_type *cpaf::gui::$(NAME)::get_impl() const
{
    return m_impl;
}
