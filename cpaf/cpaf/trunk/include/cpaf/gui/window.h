/*
Client wrapper for api::gui::Window
*/

#ifndef CPAF_GUI_WINDOW_H
#define CPAF_GUI_WINDOW_H

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/gui/toplevel.h>

namespace cpaf {
    namespace gui {

/*!
    \brief A Window is a top level widget that contains a title bar, min max and close buttons,
    and contains subwindows.
*/
class CPAF_API Window : public TopLevel
{
private:
    // not shared_ptr because this object will never be responsible for deleting this pointer
    // it only serves to save extraneous casting in source
    cpaf::api::gui::Window *m_impl;

public:
    //! \todo this should ask for a api::gui parent...
    Window(cpaf::gui::Window *parent = NULL);

protected:
    //Window(const cpaf::api::gui::WindowPtr &p);
    Window(cpaf::api::gui::Window *p);

public:
    operator cpaf::api::gui::Window *();
};

    } // gui
} // cpaf

#endif // CPAF_GUI_WINDOW_H
