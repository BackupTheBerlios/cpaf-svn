/*!
    \file src/cpaf/common/gridbaglayout.cpp
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

#include <cpaf/common/gui/gridbaglayout.h>
#include <cpaf/gui/panel.h>
#include <cpaf/flags.h>

using namespace cpaf::common::gui::gblm;
using namespace cpaf::common::gui;
using cpaf::gui::GridBagLayoutInfo;
using namespace cpaf::flags;

// need namespace declarations for template specializations (by standard)
namespace cpaf {
    namespace common {
        namespace gui {

template<> inline gblm::Groups &GridBagLayout::get_objects<COLUMN>() const
{
    return m_columns;
}

template<> inline gblm::Groups &GridBagLayout::get_objects<ROW>() const
{
    return m_rows;
}

template<> inline gblm::GroupData &GridBagLayout::get_group_data<COLUMN>(int index) const
{
    return m_columns[index];
}

template<> inline gblm::GroupData &GridBagLayout::get_group_data<ROW>(int index) const
{
    return m_rows[index];
}

template<> inline float &GridBagLayout::get_size_value<COLUMN>(cpaf::Size &size) const
{
    return size.width;
}

template<> inline float &GridBagLayout::get_size_value<ROW>(cpaf::Size &size) const
{
    return size.height;
}

template<> inline float GridBagLayout::get_size_value<COLUMN>(const cpaf::Size &size) const
{
    return size.width;
}

template<> inline float GridBagLayout::get_size_value<ROW>(const cpaf::Size &size) const
{
    return size.height;
}

template<> inline void GridBagLayout::get_pad_values<COLUMN>(const LayoutData &data, float &pad1, float &pad2) const
{
    pad1 = data.pad_left;
    pad2 = data.pad_right;
}

template<> inline void GridBagLayout::get_pad_values<ROW>(const LayoutData &data, float &pad1, float &pad2) const
{
    pad1 = data.pad_top;
    pad2 = data.pad_bottom;
}

template<> inline float GridBagLayout::get_gap<COLUMN>() const
{
    return m_column_gap;
}

template<> inline float GridBagLayout::get_gap<ROW>() const
{
    return m_row_gap;
}

template<> inline float &GridBagLayout::get_pos_value<COLUMN>(cpaf::Point &pos) const
{
    return pos.x;
}

template<> inline float &GridBagLayout::get_pos_value<ROW>(cpaf::Point &pos) const
{
    return pos.y;
}

template<> inline float GridBagLayout::get_pos_value<COLUMN>(const cpaf::Point &pos) const
{
    return pos.x;
}

template<> inline float GridBagLayout::get_pos_value<ROW>(const cpaf::Point &pos) const
{
    return pos.y;
}

template<> void GridBagLayout::get_margin_values<COLUMN>(float &margin1, float &margin2) const
{
    margin1 = m_margin_left;
    margin2 = m_margin_right;
}

template<> void GridBagLayout::get_margin_values<ROW>(float &margin1, float &margin2) const
{
    margin1 = m_margin_top;
    margin2 = m_margin_bottom;
}

template<> inline int &GridBagLayout::get_non_empty_groups<COLUMN>() const
{
    return m_non_empty_columns;
}

template<> inline int &GridBagLayout::get_non_empty_groups<ROW>() const
{
    return m_non_empty_rows;
}

template<> int GridBagLayout::get_group_span<COLUMN>(const gblm::LayoutData &data) const
{
    return data.col_span;
}

template<> int GridBagLayout::get_group_span<ROW>(const gblm::LayoutData &data) const
{
    return data.row_span;
}

        } // gui
    } // common
} // cpaf

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
    // make sure we get a chance to calculate our min size if its invalid
    update_sizes();

    return m_min_size;
}

cpaf::Size GridBagLayout::get_max_size() const
{
    // make sure we get a chance to calculate our min size if its invalid
    update_sizes();

    return m_max_size;
}

cpaf::Size GridBagLayout::get_natural_size() const
{
    // make sure we get a chance to calculate our min size if its invalid
    update_sizes();

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

template<GROUP group> inline void GridBagLayout::calc_group_sizes()
{
    Groups &info = get_objects<group>();

    if( info.empty() )
        return; // nothing to do

    // calculate sizes for each group accounting for gaps
    float margin1, margin2;
    float gap = get_gap<group>();
    float available_size = get_size_value<group>(m_rect.size);

    get_margin_values<group>(margin1, margin2);
    available_size -= (get_non_empty_groups<group>() - 1) * gap + margin1 + margin2;

    // before we begin, we must reset non persistant data stored within GroupData objects
    for( Groups::iterator i = info.begin(), end = info.end(); i != end; ++i )
        i->second.m_done = false;

    bool again;
    do
    {
        again = false;
        float weight_sum = 0;

        // current amount of space that is accounted for
        float current_size = 0;

        // see how much space is left
        for( Groups::const_iterator i = info.begin(), end = info.end(); i != end; ++i )
        {
            const GroupData &data = i->second;

            if( data.empty() )
                continue;

            if( data.m_done)
                current_size += get_size_value<group>(data.m_rect.size);
            else
                weight_sum += data.m_weight;
        }

        // distribute evenly for each group, considering mins and maxes, and starting over when need be
        float extra_size = available_size - current_size;

        for( Groups::iterator i = info.begin(), end = info.end(); i != end; ++i )
        {
            GroupData &data = i->second;

            if( data.m_done || data.empty() )
                continue;

            cpaf::Rect &rect = data.m_rect;
            float &dest_val = get_size_value<group>(rect.size);
            float min_val = data.m_min_size;

            dest_val = (extra_size * data.m_weight) / weight_sum;

            /*
                A weight value of 0 has special meaning:
                A group with weight 0 will have a maximal size equal to
                the largest natural size of its child objects.
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
            }
        }
    } while(again);

    cpaf::Point pos = m_rect.position;
    get_pos_value<group>(pos) += margin1;

    // calculate object sizes
    for( Groups::iterator gi = info.begin(); gi != info.end(); ++gi )
    {
        GroupData &data = gi->second;

        if( data.empty() )
            continue;

        for( GroupObjects::iterator oi = data.m_objects.begin(), end = data.m_objects.end(); oi != end; ++oi )
        {
            ObjectInfo &info = *(oi->second);

            cpaf::Rect &rect = info.m_rect;

            float &size_dest_val = get_size_value<group>(rect.size);
            float size_src_val_natural = 0;
            float size_src_val = get_size_value<group>(data.m_rect.size);
            float pad1, pad2; get_pad_values<group>(info.data, pad1, pad2);
            bool expand;
            int group_span = get_group_span<group>(info.data);

            // account for group spanning
            if( group_span > 1 )
            {
                Groups::iterator spanned_group = gi;
                spanned_group++;
                for( int i = 1; i < group_span; ++i, spanned_group++ )
                {
                    GroupData &data = spanned_group->second;

                    size_src_val += get_size_value<group>(data.m_rect.size) + gap;
                }
            }

            if( group == COLUMN )
            {
                expand = (info.data.flags & EXPAND_HORIZONTAL) == EXPAND_HORIZONTAL;
            }
            else
            {
                expand = (info.data.flags & EXPAND_VERTICAL) == EXPAND_VERTICAL;
            }

            // account for padding
            size_src_val -= pad1 + pad2;

            if( expand )
            {
                // if the size we would specify is larger than the widgets maximum,
                // don't expand it, just specify its size to be equal to its max and
                // use alignment flags
                float max_val = get_size_value<group>(info.m_max_size);

                if( max_val != 0 && size_src_val > max_val )
                {
                    size_dest_val = size_src_val_natural = max_val;
                    expand = false;
                }
                else
                    size_dest_val = size_src_val;
            }
            else
            {
                size_src_val_natural = get_size_value<group>(info.m_natural_size);

                // make sure the natural size isn't larger than the max or smaller than min
                float min_val = get_size_value<group>(info.m_min_size);
                float max_val = get_size_value<group>(info.m_max_size);

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
                    where = (info.data.flags & ALIGN_LEFT) == ALIGN_LEFT;
                    center = (info.data.flags & ALIGN_CENTER_HORIZONTAL) == ALIGN_CENTER_HORIZONTAL;
                }
                else
                {
                    where = (info.data.flags & ALIGN_TOP) == ALIGN_TOP;
                    center = (info.data.flags & ALIGN_CENTER_VERTICAL) == ALIGN_CENTER_VERTICAL;
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
    // update the data cache if needed
    update_sizes();

    // do all calculations for the hozirontal and vertical directions
    calc_group_sizes<COLUMN>();
    calc_group_sizes<ROW>();

    // now actually position the objects
    for( Objects::iterator i = m_objects.begin(), end = m_objects.end(); i != end; ++i )
        boost::shared_ptr<cpaf::gui::Object>(i->object)->set_rect(i->m_rect);
}

void GridBagLayout::update_sizes() const
{
    if( m_values_invalid )
    {
        // update all object min and max sizes
        for( gblm::Objects::iterator i = m_objects.begin(), end = m_objects.end(); i != end; ++i )
        {
            gblm::ObjectInfo &info = *i;

            boost::shared_ptr<cpaf::gui::Object> ptr(info.object);
            info.m_min_size = ptr->get_min_size();
            info.m_max_size = ptr->get_max_size();
            info.m_natural_size = ptr->get_natural_size();
        }

        update_group_sizes<COLUMN>();
        update_group_sizes<ROW>();

        m_values_invalid = false;
    }
}

template<GROUP group> void GridBagLayout::update_group_sizes() const
{
    Groups &groups = get_objects<group>();

    float total_min = 0;
    float gap = get_gap<group>();
    
    int &non_empty_groups = get_non_empty_groups<group>();
    non_empty_groups = 0;

    // calculate the minimum and maximum group size
    for( Groups::iterator gi = groups.begin(), gend = groups.end(); gi != gend; ++gi )
    {
        GroupData &data = gi->second;

        // skip empty groups
        if( data.empty() )
            continue;
        else
            // keep track of how many non empty groups there are for accurate gap calculations
            non_empty_groups++;

        float &min_val_total = data.m_min_size;

        for( GroupObjects::iterator i = data.m_objects.begin(), end = data.m_objects.end(); i != end; ++i )
        {
            const ObjectInfo &info = *(i->second);
            float min_val = get_size_value<group>(info.m_min_size);
            float pad1, pad2;

            get_pad_values<group>(info.data, pad1, pad2);

            // accound for padding
            if( min_val != 0 )
                min_val += pad1 + pad2;

            // honor mins
            if( min_val > min_val_total )
                min_val_total = min_val;
        }

        // calculate min size for the gblm itself
        total_min += min_val_total;
    }

    // finish calculating min
    float margin1, margin2;
    get_margin_values<group>(margin1, margin2);

    float extra = (non_empty_groups - 1) * gap + margin1 + margin2;

    // assign the GBLM's min  size value
    if( total_min > 0 )
        get_size_value<group>(m_min_size) = total_min + extra;

    // set the min size of our panel
    boost::shared_ptr<cpaf::gui::Panel> panel = m_panel.lock();
    if( panel )
        panel->set_min_size(m_min_size);
}

void GridBagLayout::add(boost::weak_ptr<cpaf::gui::Object> object, const cpaf::gui::GridBagLayoutInfo &info)
{
    LayoutData data = info.get_data();
    m_objects.push_back(ObjectInfo(object, data));

    // add this object to the quick lookup maps
    get_group_data<COLUMN>(data.col).m_objects.insert(std::make_pair(data.row, &m_objects.back()));
    get_group_data<ROW>(data.row).m_objects.insert(std::make_pair(data.col, &m_objects.back()));

    invalidate();
}

void GridBagLayout::remove(boost::weak_ptr<cpaf::gui::Object> object)
{
    gblm::Objects::iterator it;

    // see if this object is managed by this gblm
    for( it = m_objects.begin(); it != m_objects.end(); ++it )
        if( it->object.lock() == object.lock() )
            break;

    // make sure we found something
    if( it == m_objects.end() )
        return;

    // remove what we found from the lookup maps and the list
    get_group_data<ROW>(it->data.row).m_objects.erase(it->data.col);
    get_group_data<COLUMN>(it->data.col).m_objects.erase(it->data.row);
    m_objects.erase(it);

    invalidate();
}

void GridBagLayout::set_column_weight(int column, float weight)
{
    get_group_data<COLUMN>(column).m_weight = weight;
    invalidate();
}

void GridBagLayout::set_row_weight(int row, float weight)
{
    get_group_data<ROW>(row).m_weight = weight;
    invalidate();
}

void GridBagLayout::set_column_gap(float gap)
{
    m_column_gap = gap;
    invalidate();
}

void GridBagLayout::set_row_gap(float gap)
{
    m_row_gap = gap;
    invalidate();
}

void GridBagLayout::set_gap(float gap)
{
    m_row_gap = m_column_gap = gap;
    invalidate();
}

void GridBagLayout::set_margins(float margin)
{
    m_margin_left =
    m_margin_top =
    m_margin_right =
    m_margin_bottom = margin;
    invalidate();
}

void GridBagLayout::set_margins(float left, float top, float right, float bottom)
{
    m_margin_left = left;
    m_margin_top = top;
    m_margin_right = right;
    m_margin_bottom = bottom;
    invalidate();
}

void GridBagLayout::set_left_margin(float margin)
{
    m_margin_left = margin;
    invalidate();
}

void GridBagLayout::set_top_margin(float margin)
{
    m_margin_top = margin;
    invalidate();
}

void GridBagLayout::set_right_margin(float margin)
{
    m_margin_right = margin;
    invalidate();
}

void GridBagLayout::set_bottom_margin(float margin)
{
    m_margin_bottom = margin;
    invalidate();
}

float &GridBagLayout::get_column_weight(int index)
{
    return get_group_data<COLUMN>(index).m_weight;
}

float &GridBagLayout::get_row_weight(int index)
{
    return get_group_data<ROW>(index).m_weight;
}

void GridBagLayout::assign(boost::weak_ptr<cpaf::gui::Panel> panel)
{
    m_panel = panel;
}

LayoutData::LayoutData()
    : flags(ALIGN_LEFT | ALIGN_TOP),
    pad_left(0), pad_top(0), pad_right(0), pad_bottom(0),
    col(0), row(0), col_span(1), row_span(1)
{ }
