/*!
    \file include/cpaf/gui/window.h
    \brief cpaf::gui::Window declaration
    \date Created: 2005-04-05
*/

#ifndef CPAF_GUI_WINDOW_H
#define CPAF_GUI_WINDOW_H

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/gui/toplevel.h>
#include <cpaf/gui/initializer/window.h>

#include <cpaf/gui/factory.h>

namespace cpaf {
    namespace gui {

/*!
    \brief A Window is a top level widget that contains a title bar, min max and close buttons,
    and contains subwindows.
*/
class CPAF_API Window : public TopLevel
{
public:
    typedef cpaf::api::gui::Window api_type;
    typedef WindowInitializer Initializer;

private:
    // not shared_ptr because this object will never be responsible for deleting this pointer
    // it only serves to save extraneous casting in source
    cpaf::api::gui::Window *m_impl;

protected:
    Window();
    Window(cpaf::api::gui::Window *impl);
    void create(Initializer::data_type params);

public:
    operator cpaf::api::gui::Window *();
    template<typename Widget> friend Widget *cpaf::gui::factory::create_widget(typename Widget::Initializer const &);
};

    } // gui
} // cpaf

#endif // CPAF_GUI_WINDOW_H
