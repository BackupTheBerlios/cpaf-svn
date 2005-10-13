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
boost::shared_ptr<$(NAME)> $(NAME)::create(const Initializer &initializer)
{
    $(NAME) *wrapper = new $(NAME);
    return wrapper->initialize(initializer);
}

boost::shared_ptr<$(NAME)> cpaf::gui::$(NAME)::inintialize(const Initializer &initializer)
{
    // create a shared pointer for this wapper
    boost::shared_ptr<$(NAME)> ptr(this);

    // create the native widget
    Initializer::data_type params = initializer.get_data();
    params.set_wrapper(ptr);
    m_impl->create(params);

    // store the widget id / shared_ptr pair to retain the wrapper
    associate_widget_id(get_id(), ptr);

    // lastly, return the wrapper
    return ptr;
}
$(END)

cpaf::gui::$(NAME)::api_type *cpaf::gui::$(NAME)::get_impl() const
{
    return m_impl;
}
