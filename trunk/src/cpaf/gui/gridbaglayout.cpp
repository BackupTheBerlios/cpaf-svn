/*!
    \file src\cpaf\gridbaglayout.cpp
    \brief Grid Bag Layout Manager implementation
    \date Created: 2005-08-31
*/

#include <cpaf/gui/gridbaglayout.h>
#include <cpaf/gui/widget.h>
#include <vector>
#include <utility>

using namespace cpaf::gui;
using namespace cpaf::gui::gblm;

GridBagLayout::GridBagLayout()
{

}

void reset_group_done_state(GroupInfo::value_type &value)
{
    value.second.m_done = false;
}

void GridBagLayout::calc_group_sizes(bool col, int avail, WidgetRects &rects)
{
    GroupInfo info;

    // size columns first

    // find the minimum sizes for all columns
    // sum the weights for each column too
    for( Weights::iterator group = m_columns.begin(); group != m_columns.end(); ++group )
    {
        GroupData data(col ? m_col_widgets[group->first] : m_row_widgets[group->first], group->second);

        // skip empty groups
        if( data.empty() )
            continue;

        cpaf::Size min_size;

        for( GroupWidgets::iterator i = data.m_widgets.begin(), end = data.m_widgets.end(); i != end; ++i )
        {
            const WidgetInfo *const info = i->second;
            cpaf::Size min = info->widget->get_min_size();

            // accound for padding
            if( col )
            {
                min.width += info->data.pad_left + info->data.pad_right;

                if( min.width > min_size.width )
                    min_size.width = min.width;
            }
            else
            {
                min.height += info->data.pad_top + info->data.pad_left;

                if( min.height > min_size.height )
                    min_size.height = min.height;
            }
        }

        data.m_min_size = min_size;

        info.insert(std::make_pair(group->first, data));
    }

    if( info.empty() )
        return; // nothing to do

    // calculate sizes for each column
    int available_size = avail;
    bool again;
    do
    {
        again = false;
        float weight_sum = 0;

        // current amount of space taken up
        int current_size = 0;

        // see how much space is left
        for( GroupInfo::const_iterator i = info.begin(), end = info.end(); i != end; ++i )
        {
            const GroupData &data = i->second;

            if( data.m_done)
                if( col )
                    current_size += data.m_rect.size.width;
                else
                    current_size += data.m_rect.size.height;
            else
                weight_sum += data.m_weight;
        }

        // distribute evenly for each column, considering minimum width, and starting over when need be
        int extra_size = available_size - current_size;

        for( GroupInfo::iterator i = info.begin(), end = info.end(); i != end; ++i )
        {
            GroupData &data = i->second;

            if( data.m_done )
                continue;

            cpaf::Rect &rect = data.m_rect;
            float val = (extra_size * data.m_weight) / weight_sum;
            float *dest_val, *min_val;

            if( col )
            {
                dest_val = &rect.size.width;
                min_val = &data.m_min_size.width;
            }
            else
            {
                dest_val = &rect.size.height;
                min_val = &data.m_min_size.height;
            }

            *dest_val = (extra_size * data.m_weight) / weight_sum;

            // make sure minimum size is still respected
            if( *dest_val < *min_val )
            {
                *dest_val = *min_val;
                data.m_done = true; // dont size this anymore
                again = true; // need to start over
                break;
            }
        }
    } while(again);

    cpaf::Point pos;

    // calculate widget sizes
    for( GroupInfo::iterator i = info.begin(); i != info.end(); ++i )
    {
        GroupData &data = i->second;

        for( GroupWidgets::iterator i = data.m_widgets.begin(), end = data.m_widgets.end(); i != end; ++i )
        {
            const WidgetInfo *const info = i->second;

            cpaf::Rect &rect = rects[info->widget];

            float *size_dest_val, size_src_val_natural, size_src_val;
            int pad1, pad2;
            bool expand;

            if( col )
            {
                size_dest_val = &rect.size.width;
                size_src_val = data.m_rect.size.width;
                pad1 = info->data.pad_left;
                pad2 = info->data.pad_right;

                expand = (info->data.alignment_info & GridBagLayoutInfo::EXPAND_HORIZONTAL) == GridBagLayoutInfo::EXPAND_HORIZONTAL;
            }
            else
            {
                size_dest_val = &rect.size.height;
                size_src_val = data.m_rect.size.height;
                pad1 = info->data.pad_top;
                pad2 = info->data.pad_bottom;

                expand = (info->data.alignment_info & GridBagLayoutInfo::EXPAND_VERTICAL) == GridBagLayoutInfo::EXPAND_VERTICAL;
            }

            // account for padding
            size_src_val -= pad1 + pad2;

            if( expand )
                *size_dest_val = size_src_val;
            else
            {
                cpaf::Size natural_size = info->widget->get_size();

                if( col )
                    size_src_val_natural = natural_size.width;
                else
                    size_src_val_natural = natural_size.height;

                *size_dest_val = size_src_val_natural;

                // make sure the natural size isn't larger than what is available
                if( *size_dest_val > size_src_val )
                {
                    *size_dest_val = size_src_val;
                    size_src_val_natural = size_src_val;
                }
            }

            float *pos_dest_val, pos_src_val;

            if( col )
            {
                pos_dest_val = &rect.position.x;
                pos_src_val = pos.x;
            }
            else
            {
                pos_dest_val = &rect.position.y;
                pos_src_val = pos.y;
            }

            pos_src_val += pad1;

            if( expand )
                *pos_dest_val = pos_src_val;
            else
            {
                // account for alignment if we aren't expanding
                bool where; // true for left/top, false for bottom/right
                bool center;

                if( col )
                {
                    where = (info->data.alignment_info & GridBagLayoutInfo::ALIGN_LEFT) == GridBagLayoutInfo::ALIGN_LEFT;
                    center = (info->data.alignment_info & GridBagLayoutInfo::ALIGN_CENTER_H) == GridBagLayoutInfo::ALIGN_CENTER_H;
                }
                else
                {
                    where = (info->data.alignment_info & GridBagLayoutInfo::ALIGN_TOP) == GridBagLayoutInfo::ALIGN_TOP;
                    center = (info->data.alignment_info & GridBagLayoutInfo::ALIGN_CENTER_V) == GridBagLayoutInfo::ALIGN_CENTER_V;
                }

                // center flags override any other flags, so check them first
                if( center )
                    *pos_dest_val = pos_src_val + (size_src_val - size_src_val_natural) / 2;
                else
                {
                    // alignment to a given side
                    if( where ) // top/left
                        *pos_dest_val = pos_src_val;
                    else
                        *pos_dest_val = pos_src_val + size_src_val - size_src_val_natural - pad2;
                }
            }
        }

        if( col )
        {
            pos.y = 0;
            pos.x += data.m_rect.size.width;
        }
        else
        {
            pos.x = 0;
            pos.y += data.m_rect.size.height;
        }
    }
}

void GridBagLayout::do_layout(const cpaf::Size &size)
{
    WidgetRects widget_rects;

    // do all calculations for the hozirontal and vertical directions
    calc_group_sizes(true, size.width, widget_rects);
    calc_group_sizes(false, size.height, widget_rects);

    // now actually position the widgets
    for( WidgetRects::iterator i = widget_rects.begin(), end = widget_rects.end(); i != end; ++i )
        set_widget_rect(i->first, i->second);
}

void GridBagLayout::add_widget(Widget *widget, const GridBagLayoutInfo &info)
{
    LayoutData data = info.get_data();
    m_widgets.push_back(WidgetInfo(widget, data));

    // make sure default row and column weights exist
    get_row_weight(data.row);
    get_column_weight(data.col);

    // add this widget to the quick lookup maps
    m_row_widgets[data.row].insert(std::make_pair(data.col, &m_widgets.back()));
    m_col_widgets[data.col].insert(std::make_pair(data.row, &m_widgets.back()));
}

GridBagLayout &GridBagLayout::set_column_weight(int column, float weight)
{
    float &w = get_column_weight(column);
    w = weight;
    return *this;
}

GridBagLayout &GridBagLayout::set_row_weight(int row, float weight)
{
    float &w = get_row_weight(row);
    w = weight;
    return *this;
}

float &GridBagLayout::get_column_weight(int index)
{
    // insert returns a pair whos first member is an iterator pointing to the element
    // regardless of wether the element existed or not, so just return its weight
    return m_columns.insert(std::make_pair(index, DEFAULT_WEIGHT)).first->second;
}

float &GridBagLayout::get_row_weight(int index)
{
    // insert returns a pair whos first member is an iterator pointing to the element
    // regardless of wether the element existed or not, so just return its weight
    return m_rows.insert(std::make_pair(index, DEFAULT_WEIGHT)).first->second;
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
    m_data->alignment_info &= ~EXPAND_HORIZONTAL;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::align_right()
{
    m_data->alignment_info &= ~ALIGN_CENTER_H;
    m_data->alignment_info |= ALIGN_RIGHT;
    m_data->alignment_info &= ~EXPAND_HORIZONTAL;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::align_top()
{
    m_data->alignment_info &= ~ALIGN_CENTER_V;
    m_data->alignment_info |= ALIGN_TOP;
    m_data->alignment_info &= ~EXPAND_VERTICAL;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::align_bottom()
{
    m_data->alignment_info &= ~ALIGN_CENTER_V;
    m_data->alignment_info |= ALIGN_BOTTOM;
    m_data->alignment_info &= ~EXPAND_VERTICAL;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::align_center_horizontal()
{
    m_data->alignment_info |= ALIGN_CENTER_H;
    m_data->alignment_info &= ~EXPAND_HORIZONTAL;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::align_center_vertical()
{
    m_data->alignment_info |= ALIGN_CENTER_V;
    m_data->alignment_info &= ~EXPAND_VERTICAL;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::align_center()
{
    m_data->alignment_info |= ALIGN_CENTER_V;
    m_data->alignment_info |= ALIGN_CENTER_H;
    m_data->alignment_info &= ~EXPAND_BOTH;
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