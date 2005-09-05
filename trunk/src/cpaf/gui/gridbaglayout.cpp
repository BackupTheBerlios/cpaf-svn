/*!
    \file src\cpaf\gridbaglayout.cpp
    \brief Grid Bag Layout Manager implementation
    \date Created: 2005-08-31
*/

#include <cpaf/gui/gridbaglayout.h>
#include <cpaf/gui/widget.h>
#include <vector>

using namespace cpaf::gui;
using namespace cpaf::gui::gblm;

GridBagLayout::GridBagLayout()
{

}

void GridBagLayout::do_layout(const cpaf::Size &size)
{
    typedef std::map<int, const WidgetInfo * const> GroupWidgets;
    typedef std::map<cpaf::gui::Widget *, cpaf::Rect> WidgetRects;
    WidgetRects widget_rects;
    std::vector<cpaf::Size> min_sizes;
    cpaf::Size min_size_sum;
    float weight_sum = 0;

    // size columns first

    // find the minimum sizes for all columns
    // sum the weights for each column too
    for( Groups::iterator col = m_columns.begin(); col != m_columns.end(); ++col )
    {
        weight_sum += col->weight;
        cpaf::Size min_size;

        GroupWidgets &widgets = m_col_widgets[col->index];
        for( GroupWidgets::iterator i = widgets.begin(), end = widgets.end(); i != end; ++i )
        {
            const WidgetInfo *const info = i->second;
            cpaf::Size min = info->widget->get_min_size();

            // accound for padding
            //min.width += info->data.pad_left + info->data.pad_right;
            //min.height += info->data.pad_top + info->data.pad_bottom;

            if( min.height > min_size.height )
                min_size.height = min.height;
            if( min.width > min_size.width )
                min_size.width = min.width;
        }

        min_sizes.push_back(min_size);
        min_size_sum += min_size;
    }

    // distribute leftover width
    int extra_width = size.width - min_size_sum.width;

    cpaf::Point pos;

    // calculate widget widths
    for( Groups::iterator col = m_columns.begin(); col != m_columns.end(); ++col )
    {
        GroupWidgets &widgets = m_col_widgets[col->index];
        for( GroupWidgets::iterator i = widgets.begin(), end = widgets.end(); i != end; ++i )
        {
            const WidgetInfo *const info = i->second;

            cpaf::Rect &rect = widget_rects[info->widget];
            rect.size.width = extra_width * col->weight / weight_sum;
            rect.size.height = 30;
            rect.position = pos;
            pos.y += rect.size.height;
        }

        pos.y = 0;
        pos.x += extra_width * col->weight / weight_sum;
    }

    // now actually position the widgets
    for( WidgetRects::iterator i = widget_rects.begin(), end = widget_rects.end(); i != end; ++i )
        set_widget_rect(i->first, i->second);
}

void GridBagLayout::add_widget(Widget *widget, const GridBagLayoutInfo &info)
{
    LayoutData data = info.get_data();
    m_widgets.push_back(WidgetInfo(widget, data));

    // make sure default row and column weights exist
    get_row(data.row);
    get_column(data.col);

    // add this widget to the quick lookup maps
    m_row_widgets[data.row].insert(std::map<int, const WidgetInfo * const>::value_type(data.col, &m_widgets.back()));
    m_col_widgets[data.col].insert(std::map<int, const WidgetInfo * const>::value_type(data.row, &m_widgets.back()));
}

GridBagLayout &GridBagLayout::set_column_weight(int column, float weight)
{
    Group &group = get_column(column);
    group.weight = weight;
    return *this;
}

GridBagLayout &GridBagLayout::set_row_weight(int row, float weight)
{
    Group &group = get_row(row);
    group.weight = weight;
    return *this;
}

Group &GridBagLayout::get_column(int index)
{
    Group group(index, DEFAULT_WEIGHT);
    // insert returns a pair whos first member is an iterator pointing to the element
    // regardless of wether the element existed or not, so just return it
    return *(m_columns.insert(group).first);
}

Group &GridBagLayout::get_row(int index)
{
    Group group(index, DEFAULT_WEIGHT);
    // insert returns a pair whos first member is an iterator pointing to the element
    // regardless of wether the element existed or not, so just return it
    return *(m_rows.insert(group).first);
}

LayoutData::LayoutData()
: alignment_info(GridBagLayoutInfo::ALIGN_CENTER_H | GridBagLayoutInfo::ALIGN_CENTER_V),
pad_left(0), pad_top(0), pad_right(0), pad_bottom(0),
col(0), row(0), col_span(0), row_span(0)
{ }

GridBagLayoutInfo::GridBagLayoutInfo()
: m_data(new LayoutData)
{ }

GridBagLayoutInfo &GridBagLayoutInfo::align_left()
{
    m_data->alignment_info &= ~ALIGN_CENTER_H;
    m_data->alignment_info |= ALIGN_LEFT;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::align_right()
{
    m_data->alignment_info &= ~ALIGN_CENTER_H;
    m_data->alignment_info |= ALIGN_RIGHT;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::align_top()
{
    m_data->alignment_info &= ~ALIGN_CENTER_V;
    m_data->alignment_info |= ALIGN_TOP;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::align_bottom()
{
    m_data->alignment_info &= ~ALIGN_CENTER_V;
    m_data->alignment_info |= ALIGN_BOTTOM;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::align_center_horizontal()
{
    m_data->alignment_info |= ALIGN_CENTER_H;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::align_center_vertical()
{
    m_data->alignment_info |= ALIGN_CENTER_V;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::align_center()
{
    m_data->alignment_info |= ALIGN_CENTER_V;
    m_data->alignment_info |= ALIGN_CENTER_H;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::expand_horizontal()
{
    m_data->alignment_info &= ~EXPAND_BOTH;
    m_data->alignment_info |= EXPAND_HORIZONTAL;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::expand_vertical()
{
    m_data->alignment_info &= ~EXPAND_BOTH;
    m_data->alignment_info |= EXPAND_VERTICAL;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::expand_both()
{
    m_data->alignment_info |= EXPAND_BOTH;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::position(unsigned int col, unsigned int row)
{
    m_data->col = col;
    m_data->row = row;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::span(unsigned int col, unsigned int row)
{
    m_data->col_span = col;
    m_data->row_span = row;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::col_span(unsigned int span)
{
    m_data->col_span = span;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::row_span(unsigned int span)
{
    m_data->row_span = span;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::padding(int pad)
{
    m_data->pad_left = pad;
    m_data->pad_top = pad;
    m_data->pad_right = pad;
    m_data->pad_bottom = pad;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::padding(int left, int top, int right, int bottom)
{
    m_data->pad_left = left;
    m_data->pad_top = top;
    m_data->pad_right = right;
    m_data->pad_bottom = bottom;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::padding_left(int pad)
{
    m_data->pad_left = pad;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::padding_right(int pad)
{
    m_data->pad_right = pad;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::padding_top(int pad)
{
    m_data->pad_top = pad;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::padding_bottom(int pad)
{
    m_data->pad_bottom = pad;
    return *this;
}

const gblm::LayoutData &GridBagLayoutInfo::get_data() const
{
    return *(m_data.get());
}