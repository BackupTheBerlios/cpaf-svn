/*!
    \file include/cpaf/cocoa/entrybox.h
    \brief Cocoa version of cpaf::api::gui::EntryBox
    \date Created: 2005-07-14
*/

#ifndef CPAF_COCOA_GUI_ENTRYBOX_H
#define CPAF_COCOA_GUI_ENTRYBOX_H

#include <cpaf/cocoa/gui/textwidget.h>
#include <cpaf/api/gui/entrybox.h>
#include <cpaf/gui/entrybox.h>

#include <string>

namespace cpaf {
    namespace cocoa {
        namespace gui {

class EntryBox : public virtual cpaf::cocoa::gui::TextWidget, public virtual cpaf::api::gui::EntryBox
{
public:
    EntryBox() { }

    void create(const cpaf::gui::initializer::EntryBoxData &params);
    void set_password_mode(bool mode);
    bool in_password_mode();
};

        } // gui
    } // cocoa
} // cpaf

#endif
