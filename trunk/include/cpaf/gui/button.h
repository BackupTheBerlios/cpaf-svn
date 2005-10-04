/*!
    \file include/cpaf/gui/button.h
    \brief cpaf::gui::Button declaration
    \date Created: 2005-04-05
*/

#ifndef CPAF_GUI_BUTTON_H
#define CPAF_GUI_BUTTON_H

#include <cpaf/gui/widget.h>
#include <cpaf/gui/initializer/button.h>

namespace cpaf {
    namespace gui {

class CPAF_API Button : public Widget
{
public:
    typedef cpaf::api::gui::Button api_type;
    typedef ButtonInitializer Initializer;

    static boost::shared_ptr<Button> create(const Initializer &initializer);

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
    boost::shared_ptr<Button> initialize(const Initializer &initializer);

public:
    api_type *get_impl() const;
};

    } // gui
} // cpaf

#endif // CPAF_GUI_BUTTON_H
