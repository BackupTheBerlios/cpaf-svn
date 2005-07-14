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
    TextBox(cpaf::api::gui::TextBox *impl);

    /*!
        \brief Constructs the native widget using the given initialization data
    */
    void create(Initializer::data_type params);

private:
    cpaf::api::gui::TextBox *m_impl;

public:
    operator cpaf::api::gui::TextBox *();
    template<typename TextWidget> friend TextWidget *cpaf::gui::factory::create_widget(typename TextWidget::Initializer const &);
};

    } // gui
} // cpaf

#endif
