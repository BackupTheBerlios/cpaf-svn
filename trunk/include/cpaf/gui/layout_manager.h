/*!
    \file src\cpaf\layout_manager.h
    \brief Grid Bag Layout Manager declaration
    \date Created: 2005-08-24
*/

#ifndef CPAF_GUI_LAYOUTMANAGER_H
#define CPAF_GUI_LAYOUTMANAGER_H

#include <cpaf/dllimpexp.h>
#include <boost/shared_ptr.hpp>
#include <cpaf/types.h>

namespace cpaf{
    namespace gui {

        class Widget;

class CPAF_API GridBagLayoutData
{
public:
    GridBagLayoutData();

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
    float weight;
};

/*!
    Layout flags for the grid bag layout manager
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

    GridBagLayoutInfo &expand_horizontal();
    GridBagLayoutInfo &expand_vertical();
    GridBagLayoutInfo &expand_both();

    GridBagLayoutInfo &position(unsigned int col, unsigned int row);
    GridBagLayoutInfo &span(unsigned int col, unsigned int row);
    GridBagLayoutInfo &weight(float weight);
    GridBagLayoutInfo &col_span(unsigned int span);
    GridBagLayoutInfo &row_span(unsigned int span);

    GridBagLayoutInfo &padding(int pad);
    GridBagLayoutInfo &padding(int left, int top, int right, int bottom);
    GridBagLayoutInfo &padding_left(int pad);
    GridBagLayoutInfo &padding_right(int pad);
    GridBagLayoutInfo &padding_top(int pad);
    GridBagLayoutInfo &padding_bottom(int pad);

private:
    boost::shared_ptr<GridBagLayoutData> m_data;
};

/*!
    Base class for layout managers
    \todo pimpl
*/
class CPAF_API LayoutManager
{
public:
    /*!
        Updates the position and size of all managed widgets
    */
    virtual void do_layout() = 0;

protected:
    /*!
        Sets the position for a given widget
    */
    void set_widget_pos(Widget *widget, const cpaf::Point &pos);

    /*!
        Sets the size for a given widget
    */
    void set_widget_size(Widget *widget, const cpaf::Size &size);

public:
    virtual ~LayoutManager();
};

/*!
    A grid bag layout manager
    \todo pimpl
*/
class CPAF_API GridBagLayoutManager : public LayoutManager
{
public:
    void do_layout();

    /*!
        Adds a widget to this layout manager with the given layout info.
    */
    void add_widget(Widget *widget, const GridBagLayoutInfo &info);

    /*!
        Removes a widget from this layout manager
    */
    //void remove_widget(Widget *widget);
};

    } // gui
} // cpaf

#endif
