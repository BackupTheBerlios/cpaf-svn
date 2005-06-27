/*!
    \file include/cpaf/gui/button.h
    \brief cpaf::gui::Button declaration
    \date Created: 2005-04-05
*/

#ifndef CPAF_GUI_BUTTON_H
#define CPAF_GUI_BUTTON_H

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/gui/widget.h>
#include <cpaf/gui/initializer/button.h>

#include <cpaf/private/factory.h>

namespace cpaf {
    namespace gui {

class CPAF_API Button : public Widget
{
    template<typename Widget> friend Widget *cpaf::gui::factory::create_widget(typename const Widget::Initializer &);

public:
    typedef cpaf::api::gui::Button api_type;

    typedef ButtonInitializer Initializer;

    void set_label(const std::string &label);
    std::string get_label();

    operator cpaf::api::gui::Button *();

private:
    cpaf::api::gui::Button *m_impl;

protected:
    Button(cpaf::api::gui::Button *impl);
    void create(const Initializer::data_type &params);
};

    } // gui
} // cpaf

#endif // CPAF_GUI_BUTTON_H
