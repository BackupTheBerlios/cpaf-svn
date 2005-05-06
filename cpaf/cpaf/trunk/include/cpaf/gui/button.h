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
        namespace factory { class Button; }

class CPAF_API Button : public Widget
{
    friend class factory::Button;

private:
    cpaf::api::gui::Button *m_impl;

protected:
    Button(cpaf::api::gui::Button *b);

public:
    operator cpaf::api::gui::Button *();

    virtual void set_label(const std::string &label);
    virtual std::string get_label();
};

        namespace factory {

template <typename T>
class ButtonFact : public WidgetFact<T>
{
protected:
     std::string m_label;

public:
    T &label(const std::string &s)
    {
        m_label = s;
        return *dynamic_cast<T*>(this);
    }

    std::string get_label() { return m_label; }
};

class  CPAF_API Button : public ButtonFact<Button>
{
public:
    cpaf::gui::Button *create();
};

//typedef ButtonFact<ButtonFact> Button;

        } // factory
    } // gui
} // cpaf

#endif // CPAF_GUI_BUTTON_H
