/*!
    \file include/cpaf/gui/initializer/entrybox.h
    \brief Initializer classes for cpaf::gui::EntryBox
    \date Created: 2005-07-14
*/

#ifndef CPAF_GUI_INITIALIZER_ENTRYBOX_H
#define CPAF_GUI_INITIALIZER_ENTRYBOX_H

#include <cpaf/gui/initializer/textwidget.h>
#include <string>

namespace cpaf {
    namespace gui {
        namespace initializer {

/*!
    \brief initialization data for Widget creation.
*/
struct CPAF_API EntryBoxData : TextWidgetData
{
protected:
    bool m_password_mode;
    
public:
    EntryBoxData();

    void set_password_mode(bool b);
    bool get_password_mode() const;
};

/*!
    \brief Initializer class template for EntryBox creation
*/
template<class T> class EntryBox : public TextWidget<T>
{
public:
    typedef EntryBoxData data_type;

protected:
    data_type *m_data;

    EntryBox(data_type *data)
        : TextWidget<T>(data),
        m_data(data)
    { }

public:
    T &password_mode(bool mode = true)
    {
        m_data->set_password_mode(mode);
        return dynamic_cast<T&>(*this);
    }

    bool get_password_mode() const { return m_data->get_password_mode(); }

private:
    // non copyable and non assignable
    EntryBox(const EntryBox<T> &);
    EntryBox<T> &operator= (const EntryBox<T> &);
};

        } // initializer

class EntryBox;
/*!
    \brief A concrete initializer class for EntryBox creation.
*/
class CPAF_API EntryBoxInitializer : public cpaf::gui::initializer::EntryBox<EntryBoxInitializer>
{
    friend class cpaf::gui::EntryBox;

public:
    EntryBoxInitializer();

private:
    data_type get_data() const;
};

    } // gui
} // cpaf

#endif
