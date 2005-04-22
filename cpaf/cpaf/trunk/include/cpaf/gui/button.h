/*
Client wrapper for api::gui::Window
*/

#ifndef CPAF_GUI_BUTTON_H
#define CPAF_GUI_BUTTON_H

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/gui/widget.h>

#include <string>

namespace cpaf {
    namespace gui {

class CPAF_API Button : public Widget
{
private:
    cpaf::api::gui::Button *m_impl;

public:
    Button(cpaf::gui::Widget *parent);

protected:
    Button(cpaf::api::gui::Button *b);

public:
    operator cpaf::api::gui::Button *();

    virtual void set_label(const std::string &label);
    virtual std::string get_label();
};

    } // gui
} // cpaf

#endif // CPAF_GUI_BUTTON_H
