/*!
    \file include/cpaf/gui/app.h
    \brief cpaf::gui::App declaration
    \date Created: 2005-04-07
*/

#ifndef CPAF_GUI_APP_H
#define CPAF_GUI_APP_H

#include <cpaf/dllimpexp.h>
#include <cpaf/app.h>
#include <cpaf/event/event.h>

namespace cpaf {
    namespace gui {

class CPAF_API App : public cpaf::App
{
protected:
    App();

private:
    /*!
        Called by the constructor, and implemented by an implementation for port specific initialization.

        If gui initialization fails for what ever reason (no X server for a *nix port), an exception will
        be thrown.
    */
    void gui_init();

public:
    virtual bool init() = 0;

    /*
        This function must be implemented by an implementation (win32, gtk2, ...).
    */
    int run();
};

    } // gui
} // cpaf

#endif // CPAF_GUI_APP_H
