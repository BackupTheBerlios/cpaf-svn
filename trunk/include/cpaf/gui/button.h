/*!
    \file include/cpaf/gui/button.h
    \brief cpaf::gui::Button declaration
    \date Created: 2005-04-05
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

        template <typename T> T *create() const
        {
            return dynamic_cast<T*>(create(new T));
        }

        Button *create() const
        {
            return create(new Button);
        }

    protected:
        /*!
            This function creates a native widget and uses \a w to wrap it.

            \return The initialized wrapper w.
        */
        cpaf::gui::Button *create(cpaf::gui::Button *w) const;
    };

private:
    cpaf::api::gui::Button *m_impl;

protected:
    Button();
    void set_impl(cpaf::api::gui::Button *impl);

public:
    operator cpaf::api::gui::Button *();

    void set_label(const std::string &label);
    std::string get_label();
};

    } // gui
} // cpaf

#endif // CPAF_GUI_BUTTON_H
