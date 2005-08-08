/*!
    \file include/cpaf/gui/window.h
    \brief cpaf::gui::Window declaration
    \date Created: 2005-04-05
*/

#ifndef CPAF_GUI_WINDOW_H
#define CPAF_GUI_WINDOW_H

#include <cpaf/gui/toplevel.h>
#include <cpaf/gui/initializer/window.h>

#include <cpaf/gui/factory.h>

namespace cpaf {
    namespace gui {

/*!
    \brief A Window is a top level widget which has a title bar and contains subwindows
*/
class CPAF_API Window : public TopLevel
{
public:
    typedef cpaf::api::gui::Window api_type;
    typedef WindowInitializer Initializer;

private:
    api_type *m_impl;

protected:
    Window();
    Window(api_type *impl);

    /*!
        \brief Constructs the native widget using the given initialization data
    */
    void create(const Initializer &initializer);

public:
    void set_content_panel(cpaf::gui::Panel *p);
    cpaf::gui::Panel *get_content_panel() const;

public:
    operator api_type *() const;
    template<typename Widget> friend Widget *cpaf::gui::factory::create_widget(typename Widget::Initializer const &);
};

    } // gui
} // cpaf

#endif // CPAF_GUI_WINDOW_H
