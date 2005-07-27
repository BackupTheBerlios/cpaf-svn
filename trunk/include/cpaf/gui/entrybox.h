/*!
    \file include/cpaf/gui/entrybox.h
    \brief cpaf::gui::EntryBox declaration
    \date Created: 2005-07-14
*/

#ifndef CPAF_GUI_ENTRYBOX_H
#define CPAF_GUI_ENTRYBOX_H

#include <cpaf/gui/textwidget.h>
#include <cpaf/gui/initializer/entrybox.h>

#include <cpaf/gui/factory.h>

namespace cpaf {
    namespace gui {

class CPAF_API EntryBox : public TextWidget
{
public:
    typedef cpaf::api::gui::EntryBox api_type;
    typedef EntryBoxInitializer Initializer;
    
    void set_password_mode(bool mode);
    bool get_password_mode() const;

protected:
    EntryBox();
    EntryBox(api_type *impl);

    /*!
        \brief Constructs the native widget using the given initializer
    */
    void create(const Initializer &initializer);

private:
    api_type *m_impl;

public:
    operator api_type *() const;
    template<typename Widget> friend Widget *cpaf::gui::factory::create_widget(typename Widget::Initializer const &);
};

    } // gui
} // cpaf

#endif
