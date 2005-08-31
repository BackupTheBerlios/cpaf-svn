/*!
    \file src\cpaf\layout_manager.cpp
    \brief Grid Bag Layout Manager implementation
    \date Created: 2005-08-24
*/

#include <cpaf/gui/layout_manager.h>
#include <cpaf/gui/widget.h>

using namespace cpaf::gui;

LayoutManager::~LayoutManager() { }

void LayoutManager::set_widget_pos(Widget *widget, const cpaf::Point &pos)
{
    widget->set_position(pos);
}

void LayoutManager::set_widget_size(Widget *widget, const cpaf::Size &size)
{
    widget->set_size(size);
}

void GridBagLayoutManager::do_layout()
{

}

void GridBagLayoutManager::add_widget(Widget *widget, const GridBagLayoutInfo &info)
{

}

GridBagLayoutData::GridBagLayoutData()
: alignment_info(0),
pad_left(0), pad_top(0), pad_right(0), pad_bottom(0),
col(0), row(0), col_span(0), row_span(0)
{ }

GridBagLayoutInfo::GridBagLayoutInfo()
: m_data(new GridBagLayoutData)
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

GridBagLayoutInfo &GridBagLayoutInfo::weight(float weight)
{
    m_data->weight = weight;
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
