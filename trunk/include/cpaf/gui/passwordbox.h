/*!
    \file include/cpaf/gui/passwordbox.h
    \brief cpaf::gui::PasswordBox declaration
    \date Created: 
*/

#ifndef CPAF_GUI_PASSWORDBOX_H
#define CPAF_GUI_PASSWORDBOX_H

#include <cpaf/gui/textwidget.h>
#include <cpaf/gui/initializer/passwordbox.h>

#include <cpaf/gui/factory.h>

namespace cpaf {
    namespace gui {

class CPAF_API PasswordBox : public TextWidget
{
public:
    typedef cpaf::api::gui::PasswordBox api_type;
    typedef PasswordBoxInitializer Initializer;

private:
    api_type *m_impl;

protected:
    PasswordBox();
    PasswordBox(api_type *impl);

    /*!
        \brief Constructs the native widget using the given initialization data
    */
    void create(Initializer::data_type params);

public:
    operator api_type *();
    template<typename Widget> friend Widget *cpaf::gui::factory::create_widget(typename Widget::Initializer const &);
};

    } // gui
} // cpaf

#endif // CPAF_GUI_PASSWORDBOX_H
