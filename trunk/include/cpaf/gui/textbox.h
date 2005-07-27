/*!
    \file include/cpaf/gui/textbox.h
    \brief cpaf::gui::TextBox declaration
    \date Created: 2005-07-07
*/

#ifndef CPAF_GUI_TEXTBOX_H
#define CPAF_GUI_TEXTBOX_H

#include <cpaf/gui/textwidget.h>
#include <cpaf/gui/initializer/textbox.h>

#include <cpaf/gui/factory.h>

namespace cpaf {
    namespace gui {

class CPAF_API TextBox : public TextWidget
{
public:
    typedef cpaf::api::gui::TextBox api_type;
    typedef TextBoxInitializer Initializer;

protected:
    TextBox();
    TextBox(api_type *impl);

    /*!
        \brief Constructs the native widget using the given initialization data
    */
    void create(const Initializer &initializer);

private:
    api_type *m_impl;

public:
    operator api_type *() const;
    template<typename Widget> friend Widget *cpaf::gui::factory::create_widget(typename Widget::Initializer const &);
};

    } // gui
} // cpaf

#endif
