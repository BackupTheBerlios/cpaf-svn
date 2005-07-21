/*!
    \file include/cpaf/api/gui/passwordbox.h
    \brief PasswordBox interface declaration
    \date Created: 
*/

#ifndef CPAF_API_GUI_PASSWORDBOX_H
#define CPAF_API_GUI_PASSWORDBOX_H

#include <cpaf/gui/initializer/passwordbox.h>
#include <cpaf/api/gui/textwidget.h>

namespace cpaf {
    namespace api {
        namespace gui {

class PasswordBox : public virtual TextWidget
{
public:
    typedef cpaf::gui::initializer::PasswordBoxData data_type; //!< Initialization data used for PasswordBox.

    virtual void create(const data_type &init_params) = 0;
};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_PASSWORDBOX_H
