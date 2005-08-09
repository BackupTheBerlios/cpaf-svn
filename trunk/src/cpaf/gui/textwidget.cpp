/*!
    \file src/cpaf/gui/textwidget.cpp
    \brief Implementation of cpaf::gui::TextWidget
    \date Created: 2005-07-14
*/

#include <cpaf/gui/textwidget.h>
#include <cpaf/api/gui/textwidget.h>
#include <cpaf/private/factory.h>

using namespace cpaf::gui;

TextWidget::TextWidget(api_type *impl)
    : Widget(impl),
    m_impl(impl)
{ }

TextWidget::api_type *TextWidget::get_impl() const
{
    return m_impl;
}

void TextWidget::set_text(const std::string &s)
{
    m_impl->set_text(s);
}

std::string TextWidget::get_text() const
{
    return m_impl->get_text();
}

std::string TextWidget::get_text(const cpaf::TextRange &range) const
{
    return m_impl->get_text(range);
}

cpaf::text_range_t TextWidget::get_length() const
{
    return m_impl->get_length();
}

cpaf::TextRange TextWidget::get_selection_range() const
{
    return m_impl->get_selection_range();
}

void TextWidget::set_selection_range(const cpaf::TextRange &range)
{
    m_impl->set_selection_range(range);
}

bool TextWidget::get_selection_bounds(cpaf::TextRange &range) const
{
    return m_impl->get_selection_bounds(range);
}

void TextWidget::set_selection_bounds(const cpaf::TextRange &range)
{
    m_impl->set_selection_bounds(range);
}

cpaf::text_range_t TextWidget::get_insertion_point() const
{
    return m_impl->get_insertion_point();
}

void TextWidget::set_insertion_point(cpaf::text_range_t pos)
{
    m_impl->set_insertion_point(pos);
}

void TextWidget::delete_range(const cpaf::TextRange &range)
{
    m_impl->delete_range(range);
}

void TextWidget::insert_text(cpaf::text_range_t pos, const std::string &str)
{
    m_impl->insert_text(pos, str);
}

void TextWidget::set_max_length(cpaf::text_range_t len)
{
    m_impl->set_max_length(len);
}

void TextWidget::set_read_only(bool b)
{
    m_impl->set_read_only(b);
}

bool TextWidget::is_read_only() const
{
    return m_impl->is_read_only();
}
