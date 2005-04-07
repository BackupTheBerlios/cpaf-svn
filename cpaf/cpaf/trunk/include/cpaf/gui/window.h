/*
Client wrapper for api::gui::Window
*/

#ifndef _CPAF_GUI_WINDOW_H_
#define _CPAF_GUI_WINDOW_H_

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/gui/toplevel.h>

namespace cpaf {
    namespace gui {

/*!
    \brief A Window is a top level widget that contains a title bar, min max and close buttons,
    and contains subwindows.
*/
class CPAF_EXP Window : public TopLevel
{
private:
    // not shared_ptr because this object will never be responsible for deleting this pointer
    // it only serves to save extraneous casting in source
    cpaf::api::gui::Window *m_impl;

public:
    Window();
protected:
    Window(const cpaf::api::gui::WindowPtr &p);

};

    } // gui
} // cpaf

#endif // _CPAF_GUI_WINDOW_H_
