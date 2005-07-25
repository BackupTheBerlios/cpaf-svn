/**
 * \file src/cpaf/cocoa/textwidget.mm
 * \brief Implementation of cpaf::cocoa::gui::TextWidget
 * \date Created: 2005-07-14
 */

#include <cpaf/cocoa/gui/textwidget.h>
#include <cpaf/exception.h>

void cpaf::cocoa::gui::TextWidget::create(const cpaf::gui::initializer::TextWidgetData &params, id widget)
{
    cpaf::cocoa::gui::Widget::create(params, widget);
    set_text(params.m_text);
}

void cpaf::cocoa::gui::TextWidget::set_text(const std::string &s)
{
    [m_object setStringValue:[NSString stringWithUTF8String:s.c_str()]];
}

std::string cpaf::cocoa::gui::TextWidget::get_text() const
{
    return [[m_object stringValue] UTF8String];
}

std::string cpaf::cocoa::gui::TextWidget::get_text(const cpaf::TextRange &range) const
{
    return "";
}

cpaf::text_range_t cpaf::cocoa::gui::TextWidget::get_length() const
{
    return 0;
}

cpaf::TextRange cpaf::cocoa::gui::TextWidget::get_selection_range() const
{
    return 0;
}

void cpaf::cocoa::gui::TextWidget::set_selection_range(const cpaf::TextRange &range)
{

}

bool cpaf::cocoa::gui::TextWidget::get_selection_bounds(cpaf::TextRange &range) const
{
    return false;
}

void cpaf::cocoa::gui::TextWidget::set_selection_bounds(const cpaf::TextRange &range)
{

}

cpaf::text_range_t cpaf::cocoa::gui::TextWidget::get_insertion_point() const
{
    return 0;
}

void cpaf::cocoa::gui::TextWidget::set_insertion_point(cpaf::text_range_t pos)
{

}

void cpaf::cocoa::gui::TextWidget::delete_range(const cpaf::TextRange &range)
{

}

void cpaf::cocoa::gui::TextWidget::insert_text(cpaf::text_range_t pos, const std::string &str)
{

}

void cpaf::cocoa::gui::TextWidget::set_max_length(cpaf::text_range_t len)
{

}

void cpaf::cocoa::gui::TextWidget::set_read_only(bool b)
{

}

bool cpaf::cocoa::gui::TextWidget::is_read_only() const
{
    return false;
}
