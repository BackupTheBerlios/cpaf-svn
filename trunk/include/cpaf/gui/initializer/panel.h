/*!
    \file include/cpaf/gui/initializer/panel.h
    \brief Initializer classes for cpaf::gui::Panel
    \date Created: 
*/

#ifndef CPAF_GUI_INITIALIZER_PANEL_H
#define CPAF_GUI_INITIALIZER_PANEL_H

#include <cpaf/gui/initializer/widget.h>
#include <cpaf/gui/layout_manager.h>

namespace cpaf {
    namespace gui {
        namespace initializer {

/*!
    \brief initialization data for Panel creation.
*/
struct CPAF_API PanelData : WidgetData
{
protected:
    cpaf::gui::LayoutManager *m_layout_manager;

public:
    PanelData();

    void set_layout_manager(cpaf::gui::LayoutManager *manager);
    cpaf::gui::LayoutManager *get_layout_manager();
};

/*!
    \brief Initializer class template for Panel creation
*/
template<class T> class Panel : public Widget<T>
{
public:
    typedef PanelData data_type;

protected:
    data_type *m_data;

    Panel(data_type *data)
        : Widget<T>(data),
        m_data(data)
    { }

    T &layout_manager(cpaf::gui::LayoutManager *manager)
    {
        m_data->set_layout_manager(manager);
        return dynamic_cast<T&>(*this);
    }

    cpaf::gui::LayoutManager *get_layout_manager() { return m_data->get_layout_manager(); }
};

        } // initializer

class Panel;
/*!
    \brief A concrete initializer class for Panel creation.
*/
class CPAF_API PanelInitializer : public cpaf::gui::initializer::Panel<PanelInitializer>
{
    friend class cpaf::gui::Panel;
public:
    PanelInitializer();

private:
    data_type get_data() const;
};

    } // gui
} // cpaf

#endif // CPAF_GUI_INITIALIZER_PANEL_H
