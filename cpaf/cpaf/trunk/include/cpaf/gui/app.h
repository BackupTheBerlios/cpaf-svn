/*
cpaf::gui::App application class
*/

#ifndef CPAF_GUI_APP_H
#define CPAF_GUI_APP_H

#include <cpaf/app.h>
#include <cpaf/dllimpexp.h>

namespace cpaf {
    namespace gui {

class CPAF_EXP App : public cpaf::App
{
protected:
    App();

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
