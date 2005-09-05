/*!
    \file src\cpaf\gridbaglayout.h
    \brief Grid Bag Layout Manager declaration
    \date Created: 2005-08-31
*/

#ifndef CPAF_GUI_GRIDBAG_H
#define CPAF_GUI_GRIDBAG_H

#include <cpaf/gui/layoutmanager.h>
#include <boost/shared_ptr.hpp>
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
    Widget *widget;
    //! The information for this widget
    LayoutData data;

    WidgetInfo(Widget *w, const LayoutData &d) : widget(w), data(d) { }
};

typedef std::list<WidgetInfo> Widgets;
typedef std::map<int, std::map<int, const WidgetInfo * const> > WidgetGroup;

/*!
    Represents a group of widgets in the same row or column
*/
struct Group
{
    //! The index of the group
    int index;

    //! The groups's weight
    float weight;

    Group(int i, float w) : index(i), weight(w) { }

    bool operator < (const Group &other) const
    {
        return index < other.index;
    }
};

typedef std::set<Group> Groups;

        } // gblm

/*!
    Layout flags for the grid bag layout manager. The default flags
    specify that the widget will be centered both vertically and horizontally
    within its alloted space and will not be expanded in either direction.
*/
class CPAF_API GridBagLayoutInfo
{
public:
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
    boost::shared_ptr<gblm::LayoutData> m_data;

    const gblm::LayoutData &get_data() const;

    friend class GridBagLayout;
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
    void add_widget(Widget *widget, const GridBagLayoutInfo &info);

    /*!
        Sets the weight value for a given column
    */
    GridBagLayout &set_column_weight(int column, float weight);

    /*!
        Sets the weight value for a given row
    */
    GridBagLayout &set_row_weight(int row, float weight);

    /*!
        Removes a widget from this layout manager
    */
    //void remove_widget(Widget *widget);

private:
    gblm::Widgets m_widgets;
    gblm::Groups m_rows, m_columns;
    gblm::WidgetGroup m_row_widgets, m_col_widgets;

    static const int DEFAULT_WEIGHT = 1;

    /*!
        \return a reference to the existing column with this index.
            If a column for this index doesn't exist, it will be created.
    */
    gblm::Group &get_column(int index);

    /*!
        \return a reference to the existing row with this index.
            If a row for this index doesn't exist, it will be created.
    */
    gblm::Group &get_row(int index);

};

    } // gui
} // cpaf

#endif // CPAF_GUI_GRIDBAG_H
