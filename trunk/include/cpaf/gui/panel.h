/*!
    \file include/cpaf/gui/panel.h
    \brief cpaf::gui::Panel declaration
    \date Created: 
*/

#ifndef CPAF_GUI_PANEL_H
#define CPAF_GUI_PANEL_H

#include <cpaf/gui/widget.h>
#include <cpaf/gui/initializer/panel.h>

#include <cpaf/gui/factory.h>

namespace cpaf {
    namespace gui {

class CPAF_API Panel : public Widget
{
public:
    typedef cpaf::api::gui::Panel api_type;
    typedef PanelInitializer Initializer;

private:
    api_type *m_impl;

protected:
    Panel();
    Panel(api_type *impl);

    /*!
        \brief Constructs the native widget using the given initializer
    */
    void create(const Initializer &initializer);

public:
    operator api_type *() const;
    template<typename Widget> friend Widget *cpaf::gui::factory::create_widget(typename Widget::Initializer const &);
};

    } // gui
} // cpaf

#endif // CPAF_GUI_PANEL_H
