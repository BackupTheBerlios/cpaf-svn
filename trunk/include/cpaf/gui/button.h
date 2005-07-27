/*!
    \file include/cpaf/gui/button.h
    \brief cpaf::gui::Button declaration
    \date Created: 2005-04-05
*/

#ifndef CPAF_GUI_BUTTON_H
#define CPAF_GUI_BUTTON_H

#include <cpaf/gui/widget.h>
#include <cpaf/gui/initializer/button.h>

#include <cpaf/gui/factory.h>

namespace cpaf {
    namespace gui {

class CPAF_API Button : public Widget
{
public:
    typedef cpaf::api::gui::Button api_type;
    typedef ButtonInitializer Initializer;

    /*!
        \brief Sets the label of the button

        \todo Move this to the common base
    */
    void set_label(const std::string &label);

    /*!
        \return The button label

        \todo Move this to the common base
    */
    std::string get_label() const;

private:
    api_type *m_impl;

protected:
    Button();
    Button(api_type *impl);

    /*!
        \brief Constructs the native widget using the given initialization data
    */
    void create(const Initializer &initializer);

public:
    operator api_type *() const;
    template<typename Widget> friend Widget *cpaf::gui::factory::create_widget(typename Widget::Initializer const &);
};

    } // gui
} // cpaf

#endif // CPAF_GUI_BUTTON_H
