/*!
    \file include/cpaf/gui/textwidget.h
    \brief cpaf::gui::TextWidget declaration
    \date Created: 2005-07-14
*/

#ifndef CPAF_GUI_TEXTWIDGET_H
#define CPAF_GUI_TEXTWIDGET_H

#include <cpaf/gui/widget.h>
#include <cpaf/gui/initializer/textwidget.h>

#include <cpaf/gui/factory.h>

namespace cpaf {
    namespace gui {

class CPAF_API TextWidget : public Widget
{
public:
    typedef cpaf::api::gui::TextWidget api_type;
    typedef TextWidgetInitializer Initializer;

    /*!
        Sets the text of the TextWidget
    */
    void set_text(const std::string &s);

    /*!
        \return The text contained in the TextWidget
    */
    std::string get_text();

protected:
    TextWidget();
    TextWidget(cpaf::api::gui::TextWidget *impl);

private:
    cpaf::api::gui::TextWidget *m_impl;

public:
    operator cpaf::api::gui::TextWidget *();
    template<typename Widget> friend Widget *cpaf::gui::factory::create_widget(typename Widget::Initializer const &);
};

    } // gui
} // cpaf

#endif
