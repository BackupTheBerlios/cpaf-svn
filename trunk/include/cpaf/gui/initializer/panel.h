/*!
    \file include/cpaf/gui/initializer/panel.h
    \brief Initializer classes for cpaf::gui::Panel
    \date Created: 
*/

/*
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef CPAF_GUI_INITIALIZER_PANEL_H
#define CPAF_GUI_INITIALIZER_PANEL_H

#include <cpaf/gui/initializer/widget.h>
#include <cpaf/gui/layoutmanager.h>

namespace cpaf {
    namespace gui {
        namespace initializer {

/*!
    \brief initialization data for Panel creation.
*/
struct CPAF_API PanelData : WidgetData
{
protected:
    boost::shared_ptr<LayoutManager> m_layout_manager;

public:
    PanelData();

    void set_layout_manager(boost::shared_ptr<LayoutManager> manager);
    boost::shared_ptr<LayoutManager> get_layout_manager() const;
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

public:
    T &layout_manager(boost::shared_ptr<LayoutManager> manager)
    {
        m_data->set_layout_manager(manager);
        return dynamic_cast<T&>(*this);
    }

    boost::shared_ptr<LayoutManager> get_layout_manager() { return m_data->get_layout_manager(); }
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
