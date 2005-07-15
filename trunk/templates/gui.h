/*!
    \file include/cpaf/gui/$(NAME_LOWER).h
    \brief cpaf::gui::$(NAME) declaration
    \date Created: 2005-07-13
*/

#ifndef CPAF_GUI_$(NAME_UPPER)_H
#define CPAF_GUI_$(NAME_UPPER)_H

#include <cpaf/gui/$(BASE_LOWER).h>
$(IF CONSTRUCTABLE)
#include <cpaf/private/factory.h>
$(END)

namespace cpaf {
    namespace gui {

class CPAF_API $(NAME) : public $(BASE)
{
public:
    typedef cpaf::api::gui::$(NAME) api_type;
    typedef $(NAME)Initializer Initializer;

private:
    api_type *m_impl;

protected:
$(IF CONSTRUCTABLE)
    $(NAME)();
$(END)
    $(NAME)(api_type *impl);

$(IF CONSTRUCTABLE)
    /*!
        \brief Constructs the native widget using the given initialization data
    */
    void create(Initializer::data_type params);
$(END)

public:
    operator api_type *();
$(IF CONSTRUCTABLE)
    template<typename Widget> friend Widget *cpaf::gui::factory::create_widget(typename Widget::Initializer const &);
$(END)
};

    } // gui
} // cpaf

#endif
