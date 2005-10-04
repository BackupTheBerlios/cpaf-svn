/*!
    \file include/cpaf/gui/textbox.h
    \brief cpaf::gui::TextBox declaration
    \date Created: 2005-07-07
*/

#ifndef CPAF_GUI_TEXTBOX_H
#define CPAF_GUI_TEXTBOX_H

#include <cpaf/gui/textwidget.h>
#include <cpaf/gui/initializer/textbox.h>

namespace cpaf {
    namespace gui {

class CPAF_API TextBox : public TextWidget
{
public:
    typedef cpaf::api::gui::TextBox api_type;
    typedef TextBoxInitializer Initializer;

    static boost::shared_ptr<TextBox> create(const Initializer &initializer);

protected:
    TextBox();
    TextBox(api_type *impl);

    /*!
        \brief Constructs the native widget using the given initialization data
    */
    boost::shared_ptr<TextBox> initialize(const Initializer &initializer);

private:
    api_type *m_impl;

public:
    api_type *get_impl() const;
};

    } // gui
} // cpaf

#endif
