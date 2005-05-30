/*
Client wrapper for api::gui::Window
*/

#ifndef CPAF_GUI_BUTTON_H
#define CPAF_GUI_BUTTON_H

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/gui/widget.h>
#include <cpaf/gui/factory/button.h>

namespace cpaf {
    namespace gui {

class CPAF_API Button : public Widget
{
public:
    /*!
        Factory for creating button objects
    */
    class CPAF_API Factory : public cpaf::gui::factory::Button<Factory>
    {
    public:
        Factory();
        Button *create() const;
    };

private:
    cpaf::api::gui::Button *m_impl;

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
