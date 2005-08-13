/*!
    \file include/cpaf/gui/initializer/panel.h
    \brief Initializer classes for cpaf::gui::Panel
    \date Created: 
*/

#ifndef CPAF_GUI_INITIALIZER_PANEL_H
#define CPAF_GUI_INITIALIZER_PANEL_H

#include <cpaf/gui/initializer/widget.h>

namespace cpaf {
    namespace gui {
        namespace initializer {

/*!
    \brief initialization data for Panel creation.
*/
struct PanelData : WidgetData
{

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
