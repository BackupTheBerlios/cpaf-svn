/*!
    \file src\cpaf\gridbaglayout.h
    \brief Grid Bag Layout Manager declaration
    \date Created: 2005-08-31
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

#ifndef CPAF_GUI_GRIDBAG_H
#define CPAF_GUI_GRIDBAG_H

#include <cpaf/gui/layoutmanager.h>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <set>
#include <list>
#include <map>

namespace cpaf {
    namespace gui { 
        class Widget;

        /*!
            Namespace to tuck away the implementation details for the Grid Bag
            layout manager
        */
        namespace gblm {

enum GROUP {
    COLUMN,
    ROW,
};

class LayoutData
{
public:
    LayoutData();

    /*!
        Contains bit flags for expansion and alignment information
    */
    int alignment_info;

    /*!
        Padding values
    */
    int pad_left, pad_top, pad_right, pad_bottom;

    /*!
        Placement information
    */
    unsigned int col, row, col_span, row_span;
};

struct WidgetInfo
{
    //! What widget is this information for
    boost::weak_ptr<Widget> widget;
    //! The information for this widget
    LayoutData data;

    WidgetInfo(boost::weak_ptr<Widget> w, const LayoutData &d) : widget(w), data(d) { }
};

typedef std::list<WidgetInfo> Widgets;
typedef std::map<int, const WidgetInfo * const> GroupWidgets;
typedef std::map<int, GroupWidgets> WidgetGroup;
typedef std::map<int, float> Weights; // represents weights for rows and columns


/*!
    Stores information for each group for processing
*/
struct GroupData {
    GroupWidgets &m_widgets;
    bool m_done;
    float m_weight;
    float m_min_size;
    float m_max_size;
    cpaf::Rect m_rect;

    GroupData(GroupWidgets &widgets, float weight)
        : m_widgets(widgets),
        m_done(false),
        m_weight(weight),
        m_min_size(0),
        m_max_size(0)
    { }

    /*!
        \return True if this group is empty (it has no widgets)
    */
    bool empty() const { return m_widgets.empty(); }
};
typedef std::map<int, GroupData> GroupInfo;

        } // gblm

/*!
    Layout flags for the grid bag layout manager. The default flags
    specify that the widget will be centered both vertically and horizontally
    within its alloted space and will not be expanded in either direction.
*/
class CPAF_API GridBagLayoutInfo
{
public:
    GridBagLayoutInfo();

    GridBagLayoutInfo &align_left();
    GridBagLayoutInfo &align_right();
    GridBagLayoutInfo &align_top();
    GridBagLayoutInfo &align_bottom();

    GridBagLayoutInfo &align_center_horizontal();
    GridBagLayoutInfo &align_center_vertical();
    GridBagLayoutInfo &align_center();

    GridBagLayoutInfo &expand_horizontal();
    GridBagLayoutInfo &expand_vertical();
    GridBagLayoutInfo &expand_both();

    GridBagLayoutInfo &position(unsigned int col, unsigned int row);
    GridBagLayoutInfo &column(unsigned int col);
    GridBagLayoutInfo &row(unsigned int row);
    GridBagLayoutInfo &span(unsigned int col, unsigned int row);
    GridBagLayoutInfo &col_span(unsigned int span);
    GridBagLayoutInfo &row_span(unsigned int span);

    GridBagLayoutInfo &padding(int pad);
    GridBagLayoutInfo &padding(int left, int top, int right, int bottom);
    GridBagLayoutInfo &padding_left(int pad);
    GridBagLayoutInfo &padding_right(int pad);
    GridBagLayoutInfo &padding_top(int pad);
    GridBagLayoutInfo &padding_bottom(int pad);

private:
    friend class GridBagLayout;
    friend class gblm::LayoutData;

    // bit flags for alignment information
    static const int ALIGN_LEFT     = 1;
    static const int ALIGN_RIGHT    = 2;
    static const int ALIGN_CENTER_H = 3;
    static const int ALIGN_TOP      = 1 << 2;
    static const int ALIGN_BOTTOM   = 2 << 2;
    static const int ALIGN_CENTER_V = 3 << 2;
    static const int EXPAND_HORIZONTAL  = 1 << 4;
    static const int EXPAND_VERTICAL    = 2 << 4;
    static const int EXPAND_BOTH        = 3 << 4;

    boost::shared_ptr<gblm::LayoutData> m_data;

    const gblm::LayoutData &get_data() const;
};

/*!
    A grid bag layout manager
    \todo pimpl
*/
class CPAF_API GridBagLayout : public LayoutManager
{
public:
    GridBagLayout();

    void do_layout(const cpaf::Size &size);

    /*!
        Adds a widget to this layout manager with the given layout info.
    */
    void add(boost::weak_ptr<Widget> widget, const GridBagLayoutInfo &info);

    void remove(boost::weak_ptr<Widget> widget);

    /*!
        Sets the weight value for a given column
    */
    GridBagLayout &set_column_weight(int column, float weight);

    /*!
        Sets the weight value for a given row
    */
    GridBagLayout &set_row_weight(int row, float weight);

    /*!
        Specifies the amount of gap inbetween columns
    */
    GridBagLayout &set_column_gap(float gap);

    /*!
        Specifies the amount of gap inbetween rows
    */
    GridBagLayout &set_row_gap(float gap);

    /*!
        Specifies the amount of gap inbetween rows and columns
    */
    GridBagLayout &set_gap(float gap);

    /*!
        Sets the margins for all sides
    */
    GridBagLayout &set_margins(float margin);

    /*!
        Sets the margins for all sides
    */
    GridBagLayout &set_margins(float left, float top, float right, float bottom);

    /*!
        Sets the left margin
    */
    GridBagLayout &set_left_margin(float margin);

    /*!
        Sets the top margin
    */
    GridBagLayout &set_top_margin(float margin);

    /*!
        Sets the right margin
    */
    GridBagLayout &set_right_margin(float margin);

    /*!
        Sets the bottom margin
    */
    GridBagLayout &set_bottom_margin(float margin);

    /*!
        Removes a widget from this layout manager
    */
    //void remove_widget(Widget *widget);

private:
    typedef std::map<boost::shared_ptr<cpaf::gui::Widget>, cpaf::Rect> WidgetRects;

    gblm::Widgets m_widgets;
    gblm::Weights m_rows, m_columns;
    gblm::WidgetGroup m_row_widgets, m_col_widgets;
    float m_row_gap, m_column_gap;
    float m_margin_top, m_margin_left, m_margin_right, m_margin_bottom;

    static const int DEFAULT_WEIGHT = 1;

    /*!
        \return a reference to the existing column with this index.
            If a column for this index doesn't exist, it will be created.
    */
    float &get_column_weight(int index);

    /*!
        \return a reference to the existing row with this index.
            If a row for this index doesn't exist, it will be created.
    */
    float &get_row_weight(int index);

    /*!
        Calculates the sizes of the widgets contained in this objects columns or rows
        based on the template parameter
    */
    template<gblm::GROUP> void calc_group_sizes(float avail, WidgetRects &rects);

    /*!
        \return Weights for the widgets in the given row or column based on the
            template parameter.
    */
    template<gblm::GROUP> gblm::Weights &get_weights();

    /*!
        \return The widgets indexed by rows or columns based on the template parameter
    */
    template<gblm::GROUP> gblm::WidgetGroup &get_widgets();

    /*!
        Calculates the minimum size in the given direction based on the template parameter
    */
    

    /*!
        \return A reference to the height or width of the given size based on the template parameter
    */
    template<gblm::GROUP> float &get_size_value(cpaf::Size &size);

    /*!
        \return The height of width of the given size based on the template parameter.
    */
    template<gblm::GROUP> float get_size_value(const cpaf::Size &size);

    /*!
        \return A reference to the x or y value of the given position based on the template parameter
    */
    template<gblm::GROUP> float &get_pos_value(cpaf::Point &pos);

    /*!
        Returns either the left and right or top and bottom padding values from the given data
            based on the template parameter through the pad1 and pad2 arguments.
    */
    template<gblm::GROUP> void get_pad_values(const gblm::LayoutData &data, float &pad1, float &pad2);

    /*!
        Returns either the left and right or top and bottom margin values
            based on the template parameter through the margin1 and margin2 arguments.
    */
    template<gblm::GROUP> void get_margin_values(float &margin1, float &margin2);

    /*!
        \return The gap between rows or columns based on the template parameter
    */
    template<gblm::GROUP> float get_gap();
};

    } // gui
} // cpaf

#endif // CPAF_GUI_GRIDBAG_H
