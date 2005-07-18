/*!
    \file include/cpaf/win32/entrybox.h
    \brief win32 version of cpaf::api::gui::EntryBox
    \date Created: 2005-07-13
*/

#ifndef CPAF_WIN32_GUI_ENTRYBOX_H
#define CPAF_WIN32_GUI_ENTRYBOX_H

#include <cpaf/win32/gui/textwidget.h>
#include <cpaf/api/gui/entrybox.h>
#include <cpaf/gui/entrybox.h>

namespace cpaf {
    namespace win32 {
        namespace gui {

class EntryBox : public virtual cpaf::win32::gui::TextWidget, public virtual cpaf::api::gui::EntryBox
{
public:
    void create(const cpaf::gui::initializer::EntryBoxData &params);
};

        } // gui
    } // win32
} // cpaf

#endif
