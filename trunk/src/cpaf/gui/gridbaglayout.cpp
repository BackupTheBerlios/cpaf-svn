/*!
    \file src/cpaf/gridbaglayout.cpp
    \brief Grid Bag Layout Manager implementation
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

#include <cpaf/gui/gridbaglayout.h>
#include <cpaf/gui/widget.h>
#include <cpaf/common/gui/gridbaglayout.h>

#include <vector>
#include <utility>

using namespace cpaf::gui;

GridBagLayoutInfo::GridBagLayoutInfo()
: m_data(new cpaf::common::gui::gblm::LayoutData)
{ }

GridBagLayoutInfo &GridBagLayoutInfo::flags(int flags)
{
    // we do not validate the sanity of the flags, it is up to the programmer to verify
    // that nonsensical combinations aren't specified. The behavior for nonsensical flags
    // is officially undefined.
    m_data->flags = flags;
    return *this;
}

int GridBagLayoutInfo::get_flags() const
{
    return m_data->flags;
}

GridBagLayoutInfo &GridBagLayoutInfo::add_flags(int flags)
{
    m_data->flags |= flags;
    return *this;
}

GridBagLayoutInfo &GridBagLayoutInfo::remove_flags(int flags)
{
    m_data->flags &= ~flags;
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

const cpaf::common::gui::gblm::LayoutData &GridBagLayoutInfo::get_data() const
{
    return *(m_data.get());
}

GridBagLayout::GridBagLayout()
: LayoutManager(new cpaf::common::gui::GridBagLayout)
{
    m_impl = get_impl<cpaf::common::gui::GridBagLayout>();
}

void GridBagLayout::add(boost::weak_ptr<Object> object, const GridBagLayoutInfo &info)
{
    m_impl->add(object, info);
}

GridBagLayout &GridBagLayout::set_column_weight(int column, float weight)
{
    m_impl->set_column_weight(column, weight);
    return *this;
}

GridBagLayout &GridBagLayout::set_row_weight(int row, float weight)
{
    m_impl->set_row_weight(row, weight);
    return *this;
}

GridBagLayout &GridBagLayout::set_column_gap(float gap)
{
    m_impl->set_column_gap(gap);
    return *this;
}

GridBagLayout &GridBagLayout::set_row_gap(float gap)
{
    m_impl->set_row_gap(gap);
    return *this;
}

GridBagLayout &GridBagLayout::set_gap(float gap)
{
    m_impl->set_gap(gap);
    return *this;
}

GridBagLayout &GridBagLayout::set_margins(float margin)
{
    m_impl->set_margins(margin);
    return *this;
}

GridBagLayout &GridBagLayout::set_margins(float left, float top, float right, float bottom)
{
    m_impl->set_margins(left, top, right, bottom);
    return *this;
}

GridBagLayout &GridBagLayout::set_left_margin(float margin)
{
    m_impl->set_left_margin(margin);
    return *this;
}

GridBagLayout &GridBagLayout::set_top_margin(float margin)
{
    m_impl->set_top_margin(margin);
    return *this;
}

GridBagLayout &GridBagLayout::set_right_margin(float margin)
{
    m_impl->set_right_margin(margin);
    return *this;
}

GridBagLayout &GridBagLayout::set_bottom_margin(float margin)
{
    m_impl->set_bottom_margin(margin);
    return *this;
}
