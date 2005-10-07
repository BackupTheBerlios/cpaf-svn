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
    : m_row_gap(0),
    m_column_gap(0),
    m_margin_top(0),
    m_margin_left(0),
    m_margin_right(0),
    m_margin_bottom(0)
{

}

inline void reset_group_done_state(GroupInfo::value_type &value)
{
    value.second.m_done = false;
}

// need namespace declarations for template specializations (by standard)
namespace cpaf {
    namespace gui {

template<> inline gblm::Weights &GridBagLayout::get_weights<COLUMN>()
{
    return m_columns;
}

template<> inline gblm::Weights &GridBagLayout::get_weights<ROW>()
{
    return m_rows;
}

template<> inline gblm::WidgetGroup &GridBagLayout::get_widgets<COLUMN>()
{
    return m_col_widgets;
}

template<> inline gblm::WidgetGroup &GridBagLayout::get_widgets<ROW>()
{
    return m_row_widgets;
}

template<> inline float &GridBagLayout::get_size_value<COLUMN>(cpaf::Size &size)
{
    return size.width;
}

template<> inline float &GridBagLayout::get_size_value<ROW>(cpaf::Size &size)
{
    return size.height;
}

template<> inline float GridBagLayout::get_size_value<COLUMN>(const cpaf::Size &size)
{
    return size.width;
}

template<> inline float GridBagLayout::get_size_value<ROW>(const cpaf::Size &size)
{
    return size.height;
}

template<> inline void GridBagLayout::get_pad_values<COLUMN>(const LayoutData &data, float &pad1, float &pad2)
{
    pad1 = data.pad_left;
    pad2 = data.pad_right;
}

template<> inline void GridBagLayout::get_pad_values<ROW>(const LayoutData &data, float &pad1, float &pad2)
{
    pad1 = data.pad_top;
    pad2 = data.pad_bottom;
}

template<> inline float GridBagLayout::get_gap<COLUMN>()
{
    return m_column_gap;
}

template<> inline float GridBagLayout::get_gap<ROW>()
{
    return m_row_gap;
}

template<> inline float &GridBagLayout::get_pos_value<COLUMN>(cpaf::Point &pos)
{
    return pos.x;
}

template<> inline float &GridBagLayout::get_pos_value<ROW>(cpaf::Point &pos)
{
    return pos.y;
}

template<> void GridBagLayout::get_margin_values<COLUMN>(float &margin1, float &margin2)
{
    margin1 = m_margin_left;
    margin2 = m_margin_right;
}

template<> void GridBagLayout::get_margin_values<ROW>(float &margin1, float &margin2)
{
    margin1 = m_margin_top;
    margin2 = m_margin_bottom;
}

    } // gui
} // cpaf

template<GROUP group> inline void GridBagLayout::calc_group_sizes(float avail, WidgetRects &rects)
{
    GroupInfo info;

    // find the minimum sizes for all groups
    // sum the weights for each group too
    for( Weights::iterator gi = get_weights<group>().begin(); gi != get_weights<group>().end(); ++gi )
    {
        GroupData data(get_widgets<group>()[gi->first], gi->second);

        // skip empty groups
        if( data.empty() )
            continue;

        float &min_val_total = data.m_min_size;
        float &max_val_total = data.m_max_size;

        for( GroupWidgets::iterator i = data.m_widgets.begin(), end = data.m_widgets.end(); i != end; ++i )
        {
            const WidgetInfo &info = *(i->second);
            float min_val = get_size_value<group>(info.widget->get_min_size());
            float max_val = get_size_value<group>(info.widget->get_max_size());
            float pad1, pad2;

            get_pad_values<group>(info.data, pad1, pad2);

            // accound for padding
            if( min_val != 0 )
                min_val += pad1 + pad2;
            if( max_val != 0 )
                max_val += pad1 + pad2;

            // honor mins and maxes
            if( min_val > min_val_total )
                min_val_total = min_val;
            if( max_val > max_val_total )
                max_val_total = max_val;
        }

        info.insert(std::make_pair(gi->first, data));
    }

    if( info.empty() )
        return; // nothing to do

    // calculate sizes for each group accounting for gaps
    float margin1, margin2;
    float available_size = avail;
    float gap = get_gap<group>();

    get_margin_values<group>(margin1, margin2);
    available_size -= (info.size() - 1) * gap + margin1 + margin2;;

    bool again;
    do
    {
        again = false;
        float weight_sum = 0;

        // current amount of space that is accounted for
        float current_size = 0;

        // see how much space is left
        for( GroupInfo::const_iterator i = info.begin(), end = info.end(); i != end; ++i )
        {
            const GroupData &data = i->second;

            if( data.m_done)
                current_size += get_size_value<group>(data.m_rect.size);
            else
                weight_sum += data.m_weight;
        }

        // distribute evenly for each group, considering mins and maxes, and starting over when need be
        float extra_size = available_size - current_size;

        for( GroupInfo::iterator i = info.begin(), end = info.end(); i != end; ++i )
        {
            GroupData &data = i->second;

            if( data.m_done )
                continue;

            cpaf::Rect &rect = data.m_rect;
            float &dest_val = get_size_value<group>(rect.size);
            float min_val = data.m_min_size;
            float max_val = data.m_max_size;

            dest_val = (extra_size * data.m_weight) / weight_sum;

            /*
                A weight value of 0 has special meaning:
                A group with weight 0 will have a maximal size equal to
                the largest natural size of its child widgets.
            */
            if( data.m_weight == 0 )
            {
                dest_val = min_val;

                // done sizing this group, start over
                data.m_done = again = true;
                break;
            }
            else
            {
                // make sure minimum size is still respected
                if( dest_val < min_val )
                {
                    dest_val = min_val;

                    // done sizing this group, start over
                    data.m_done = again = true;
                    break;
                }
                // make sure maximal size is still respected
                if( max_val != 0 && dest_val > max_val )
                {
                    dest_val = max_val;

                    // done sizing this group, start over
                    data.m_done = again = true;
                    break;
                }
            }
        }
    } while(again);

    cpaf::Point pos;
    get_pos_value<group>(pos) = margin1;

    // calculate widget sizes
    for( GroupInfo::iterator i = info.begin(); i != info.end(); ++i )
    {
        GroupData &data = i->second;

        for( GroupWidgets::iterator i = data.m_widgets.begin(), end = data.m_widgets.end(); i != end; ++i )
        {
            const WidgetInfo &info = *(i->second);

            cpaf::Rect &rect = rects[info.widget];

            float &size_dest_val = get_size_value<group>(rect.size);
            float size_src_val_natural = 0;
            float size_src_val = get_size_value<group>(data.m_rect.size);
            float pad1, pad2;
            bool expand;

            get_pad_values<group>(info.data, pad1, pad2);

            if( group == COLUMN )
            {
                expand = (info.data.alignment_info & GridBagLayoutInfo::EXPAND_HORIZONTAL) == GridBagLayoutInfo::EXPAND_HORIZONTAL;
            }
            else
            {
                expand = (info.data.alignment_info & GridBagLayoutInfo::EXPAND_VERTICAL) == GridBagLayoutInfo::EXPAND_VERTICAL;
            }

            // account for padding
            size_src_val -= pad1 + pad2;

            if( expand )
                size_dest_val = size_src_val;
            else
            {
                size_src_val_natural = get_size_value<group>(info.widget->get_natural_size());

                // make sure the natural size isn't larger than the max or smaller than min
                float min_val = data.m_min_size;
                float max_val = data.m_max_size;

                if( min_val != 0 && size_src_val_natural < min_val )
                    size_src_val_natural = min_val;
                if( max_val != 0 && size_src_val_natural > max_val )
                    size_src_val_natural = max_val;

                // make sure the natural size isn't larger than what is available
                if( size_src_val_natural > size_src_val )
                    size_src_val_natural = size_src_val;

                size_dest_val = size_src_val_natural;
            }

            float &pos_dest_val = get_pos_value<group>(rect.position);
            float pos_src_val = get_pos_value<group>(pos);

            pos_src_val += pad1;

            if( expand )
                pos_dest_val = pos_src_val;
            else
            {
                // account for alignment if we aren't expanding
                bool where; // true for left/top, false for bottom/right
                bool center;

                if( group == COLUMN )
                {
                    where = (info.data.alignment_info & GridBagLayoutInfo::ALIGN_LEFT) == GridBagLayoutInfo::ALIGN_LEFT;
                    center = (info.data.alignment_info & GridBagLayoutInfo::ALIGN_CENTER_H) == GridBagLayoutInfo::ALIGN_CENTER_H;
                }
                else
                {
                    where = (info.data.alignment_info & GridBagLayoutInfo::ALIGN_TOP) == GridBagLayoutInfo::ALIGN_TOP;
                    center = (info.data.alignment_info & GridBagLayoutInfo::ALIGN_CENTER_V) == GridBagLayoutInfo::ALIGN_CENTER_V;
                }

                // center flags override any other flags, so check them first
                if( center )
                    pos_dest_val = pos_src_val + (size_src_val - size_src_val_natural) / 2;
                else
                {
                    // alignment to a given side
                    if( where ) // top/left
                        pos_dest_val = pos_src_val;
                    else // bottom/right
                        pos_dest_val = pos_src_val + size_src_val - size_src_val_natural - pad2;
                }
            }
        }

        get_pos_value<group>(pos) += get_size_value<group>(data.m_rect.size) + gap;
    }
}

void GridBagLayout::do_layout(const cpaf::Size &size)
{
    WidgetRects widget_rects;

    // do all calculations for the hozirontal and vertical directions
    calc_group_sizes<COLUMN>(size.width, widget_rects);
    calc_group_sizes<ROW>(size.height, widget_rects);

    // now actually position the widgets
    for( WidgetRects::iterator i = widget_rects.begin(), end = widget_rects.end(); i != end; ++i )
        set_widget_rect(i->first, i->second);
}

void GridBagLayout::add(boost::shared_ptr<Widget> widget, const GridBagLayoutInfo &info)
{
    LayoutData data = info.get_data();
    m_widgets.push_back(WidgetInfo(widget.get(), data));

    // make sure default row and column weights exist
    get_row_weight(data.row);
    get_column_weight(data.col);

    // add this widget to the quick lookup maps
    m_row_widgets[data.row].insert(std::make_pair(data.col, &m_widgets.back()));
    m_col_widgets[data.col].insert(std::make_pair(data.row, &m_widgets.back()));
}

void GridBagLayout::remove(boost::shared_ptr<Widget> widget)
{
    gblm::Widgets::iterator it;

    // see if this widget is managed by this gblm
    for( it = m_widgets.begin(); it != m_widgets.end(); ++it )
        if( it->widget == widget.get() )
            break;

    // make sure we found something
    if( it == m_widgets.end() )
        return;

    // remove what we found from the lookup maps and the list
    m_row_widgets[it->data.row].erase(it->data.col);
    m_col_widgets[it->data.col].erase(it->data.row);
    m_widgets.erase(it);
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

GridBagLayout &GridBagLayout::set_column_gap(float gap)
{
    m_column_gap = gap;
    return *this;
}

GridBagLayout &GridBagLayout::set_row_gap(float gap)
{
    m_row_gap = gap;
    return *this;
}

GridBagLayout &GridBagLayout::set_gap(float gap)
{
    m_row_gap = m_column_gap = gap;
    return *this;
}

GridBagLayout &GridBagLayout::set_margins(float margin)
{
    m_margin_left =
    m_margin_top =
    m_margin_right =
    m_margin_bottom = margin;
    return *this;
}

GridBagLayout &GridBagLayout::set_margins(float left, float top, float right, float bottom)
{
    m_margin_left = left;
    m_margin_top = top;
    m_margin_right = right;
    m_margin_bottom = bottom;
    return *this;
}

GridBagLayout &GridBagLayout::set_left_margin(float margin)
{
    m_margin_left = margin;
    return *this;
}

GridBagLayout &GridBagLayout::set_top_margin(float margin)
{
    m_margin_top = margin;
    return *this;
}

GridBagLayout &GridBagLayout::set_right_margin(float margin)
{
    m_margin_right = margin;
    return *this;
}

GridBagLayout &GridBagLayout::set_bottom_margin(float margin)
{
    m_margin_bottom = margin;
    return *this;
}


float &GridBagLayout::get_column_weight(int index)
{
    // insert returns a pair whos first member is an iterator pointing to the element
    // regardless of whether the element existed or not, so just return its weight
    return m_columns.insert(std::make_pair(index, DEFAULT_WEIGHT)).first->second;
}

float &GridBagLayout::get_row_weight(int index)
{
    // insert returns a pair whos first member is an iterator pointing to the element
    // regardless of whether the element existed or not, so just return its weight
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
    m_data->alignment_info &= ~ALIGN_CENTER_H;
    m_data->alignment_info &= ~EXPAND_BOTH;
    m_data->alignment_info |= EXPAND_HORIZONTAL;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::expand_vertical()
{
    m_data->alignment_info &= ~ALIGN_CENTER_V;
    m_data->alignment_info &= ~EXPAND_BOTH;
    m_data->alignment_info |= EXPAND_VERTICAL;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::expand_both()
{
    m_data->alignment_info &= ~ALIGN_CENTER_V;
    m_data->alignment_info &= ~ALIGN_CENTER_H;
    m_data->alignment_info |= EXPAND_BOTH;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::position(unsigned int col, unsigned int row)
{
    m_data->col = col;
    m_data->row = row;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::column(unsigned int col)
{
    m_data->col = col;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::row(unsigned int row)
{
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
