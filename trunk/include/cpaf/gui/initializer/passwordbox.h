/*!
    \file include/cpaf/gui/initializer/passwordbox.h
    \brief Initializer classes for cpaf::gui::PasswordBox
    \date Created: 
*/

#ifndef CPAF_GUI_INITIALIZER_PASSWORDBOX_H
#define CPAF_GUI_INITIALIZER_PASSWORDBOX_H

#include <cpaf/gui/initializer/passwordbox.h>

namespace cpaf {
    namespace gui {
        namespace initializer {

/*!
    \brief initialization data for PasswordBox creation.
*/
struct PasswordBoxData : TextWidgetData
{

};

/*!
    \brief Initializer class template for PasswordBox creation
*/
template<class T> class PasswordBox : public TextWidget<T>
{
public:
    typedef PasswordBoxData data_type;

protected:
    data_type *m_data;

    PasswordBox(data_type *data)
        : TextWidget<T>(data),
        m_data(data)
    { }
};

        } // initializer

/*!
    \brief A concrete initializer class for PasswordBox creation.
*/
class PasswordBoxInitializer : public cpaf::gui::initializer::PasswordBox<PasswordBoxInitializer>
{
public:
    PasswordBoxInitializer()
        : cpaf::gui::initializer::PasswordBox<PasswordBoxInitializer>(new cpaf::gui::initializer::PasswordBoxData)
    { }

    operator cpaf::gui::initializer::PasswordBoxData () const
    {
        return *m_data;
    }
};

    } // gui
} // cpaf

#endif // CPAF_GUI_INITIALIZER_PASSWORDBOX_H