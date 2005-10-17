/*!
    \file src/cpaf/gui/gblmimpl.cpp
    \brief Grid Bag Layout Manager implementation
    \date Created: 2005-10-16
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

#include <cpaf/gui/gblmimpl.h>
#include <cpaf/gui/widget.h>

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

void GridBagLayout::set_size(const cpaf::Size &size)
{
    m_rect.size = size;
    update_layout();
}

void GridBagLayout::set_min_size(const cpaf::Size &size)
{
    //! \todo Decide whether to honor specified sizes
}

void GridBagLayout::set_max_size(const cpaf::Size &size)
{
    //! \todo Decide whether to honor specified sizes
}

void GridBagLayout::set_natural_size(const cpaf::Size &size)
{
    //! \todo Decide whether to honor specified sizes
}

void GridBagLayout::set_position(const cpaf::Point &pos)
{
    m_rect.position = pos;
    update_layout();
}

void GridBagLayout::set_rect(const cpaf::Rect &rect)
{
    m_rect = rect;
    update_layout();
}

cpaf::Size GridBagLayout::get_size() const
{
    return m_rect.size;
}

cpaf::Size GridBagLayout::get_min_size() const
{
    return m_min_size;
}

cpaf::Size GridBagLayout::get_max_size() const
{
    return m_max_size;
}

cpaf::Size GridBagLayout::get_natural_size() const
{
    return m_natural_size;
}

cpaf::Point GridBagLayout::get_position() const
{
    return m_rect.position;
}

cpaf::Rect GridBagLayout::get_rect() const
{
    return m_rect;
}

void GridBagLayout::invalidate()
{
    m_values_invalid = true;
}

template<GROUP group> inline void GridBagLayout::calc_group_sizes(const cpaf::Rect &avail, WidgetRects &rects)
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
            float min_val = get_size_value<group>(info.widget.lock()->get_min_size());
            float max_val = get_size_value<group>(info.widget.lock()->get_max_size());
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
    float gap = get_gap<group>();
    float available_size = get_size_value<group>(avail.size);

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

    cpaf::Point pos = avail.position;
    get_pos_value<group>(pos) += margin1;

    // calculate widget sizes
    for( GroupInfo::iterator i = info.begin(); i != info.end(); ++i )
    {
        GroupData &data = i->second;

        for( GroupWidgets::iterator i = data.m_widgets.begin(), end = data.m_widgets.end(); i != end; ++i )
        {
            const WidgetInfo &info = *(i->second);

            cpaf::Rect &rect = rects[info.widget.lock()];

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
                size_src_val_natural = get_size_value<group>(info.widget.lock()->get_natural_size());

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

void GridBagLayout::update_layout()
{
    WidgetRects widget_rects;

    // do all calculations for the hozirontal and vertical directions
    calc_group_sizes<COLUMN>(m_rect, widget_rects);
    calc_group_sizes<ROW>(m_rect, widget_rects);

    // now actually position the widgets
    for( WidgetRects::iterator i = widget_rects.begin(), end = widget_rects.end(); i != end; ++i )
        i->first->set_rect(i->second);
}

void GridBagLayout::add(boost::weak_ptr<cpaf::gui::Widget> widget, const cpaf::gui::GridBagLayoutInfo &info)
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

void GridBagLayout::remove(boost::weak_ptr<cpaf::gui::Widget> widget)
{
    gblm::Widgets::iterator it;

    // see if this widget is managed by this gblm
    for( it = m_widgets.begin(); it != m_widgets.end(); ++it )
        if( it->widget.lock() == widget.lock() )
            break;

    // make sure we found something
    if( it == m_widgets.end() )
        return;

    // remove what we found from the lookup maps and the list
    m_row_widgets[it->data.row].erase(it->data.col);
    m_col_widgets[it->data.col].erase(it->data.row);
    m_widgets.erase(it);
}

void GridBagLayout::set_column_weight(int column, float weight)
{
    float &w = get_column_weight(column);
    w = weight;
}

void GridBagLayout::set_row_weight(int row, float weight)
{
    float &w = get_row_weight(row);
    w = weight;
}

void GridBagLayout::set_column_gap(float gap)
{
    m_column_gap = gap;
}

void GridBagLayout::set_row_gap(float gap)
{
    m_row_gap = gap;
}

void GridBagLayout::set_gap(float gap)
{
    m_row_gap = m_column_gap = gap;
}

void GridBagLayout::set_margins(float margin)
{
    m_margin_left =
    m_margin_top =
    m_margin_right =
    m_margin_bottom = margin;
}

void GridBagLayout::set_margins(float left, float top, float right, float bottom)
{
    m_margin_left = left;
    m_margin_top = top;
    m_margin_right = right;
    m_margin_bottom = bottom;
}

void GridBagLayout::set_left_margin(float margin)
{
    m_margin_left = margin;
}

void GridBagLayout::set_top_margin(float margin)
{
    m_margin_top = margin;
}

void GridBagLayout::set_right_margin(float margin)
{
    m_margin_right = margin;
}

void GridBagLayout::set_bottom_margin(float margin)
{
    m_margin_bottom = margin;
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

// need namespace declarations for template specializations (by standard)
namespace cpaf {
    namespace gui {
        namespace gblm {

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

template<> inline float GridBagLayout::get_pos_value<COLUMN>(const cpaf::Point &pos)
{
    return pos.x;
}

template<> inline float GridBagLayout::get_pos_value<ROW>(const cpaf::Point &pos)
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

        } // gblm
    } // gui
} // cpaf