/*!
    \file src/cpaf/cocoa/textbox.mm
    \brief Implementation of cpaf::cocoa::gui::TextBox
    \date Created: 2005-07-08
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

#include <cpaf/cocoa/gui/textbox.h>
#include <cpaf/exception.h>

CPAF_COCOA_INTERFACE(ScrollView)
CPAF_COCOA_IMPLEMENTATION(ScrollView)

void cpaf::cocoa::gui::TextBox::create(const cpaf::gui::initializer::TextBoxData &params)
{
    NSSize size;

    if( !params.get_parent() )
        throw cpaf::Exception(cpaf::Exception::WIDGET_NO_PARENT, __LINE__, __FILE__);

    // Initialize the NSTextView, before calling TextWidget::create() (because this will call set_text())
    m_textview = [[NSTextView alloc] init];

    cpaf::cocoa::gui::TextWidget::create(params, [[CpafScrollView alloc] init]);

    // Set up the NSScrollView
    [m_object setHasVerticalScroller:YES];
    [m_object setAutohidesScrollers:YES];
    [m_object setBorderType:NSBezelBorder];

    // Get the size of the NSScrollView and resize the NSTextView
    size = [m_object frame].size;
    [m_textview setFrame:NSMakeRect(0.0, 0.0, size.width, size.height)];

    // Autosize, so the NSTextView is always as big as the NSScrollView
    [m_textview setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];

    [m_textview setRichText:NO];
    [m_textview setUsesFontPanel:NO]; // Don't allow changing the font

    // Add the NSTextView to the NSScrollView
    [m_object setDocumentView:m_textview];
    [m_textview release];

    send_event(cpaf::event::WIDGET_CREATE);
}

void cpaf::cocoa::gui::TextBox::set_text(const std::string &s)
{
    [m_textview setString:[NSString stringWithUTF8String:s.c_str()]];
}

std::string cpaf::cocoa::gui::TextBox::get_text() const
{
    return [[m_textview string] UTF8String];
}

std::string cpaf::cocoa::gui::TextBox::get_text(const cpaf::TextRange &range) const
{
    return "";
}

cpaf::text_range_t cpaf::cocoa::gui::TextBox::get_length() const
{
    return 0;
}

cpaf::TextRange cpaf::cocoa::gui::TextBox::get_selection_range() const
{
    return 0;
}

void cpaf::cocoa::gui::TextBox::set_selection_range(const cpaf::TextRange &range)
{

}

bool cpaf::cocoa::gui::TextBox::get_selection_bounds(cpaf::TextRange &range) const
{
    return false;
}

void cpaf::cocoa::gui::TextBox::set_selection_bounds(const cpaf::TextRange &range)
{

}

cpaf::text_range_t cpaf::cocoa::gui::TextBox::get_insertion_point() const
{
    return 0;
}

void cpaf::cocoa::gui::TextBox::set_insertion_point(cpaf::text_range_t pos)
{

}

void cpaf::cocoa::gui::TextBox::delete_range(const cpaf::TextRange &range)
{

}

cpaf::text_range_t cpaf::cocoa::gui::TextBox::insert_text(const std::string &str, cpaf::text_range_t pos)
{
    return 0;
}

cpaf::text_range_t cpaf::cocoa::gui::TextBox::insert_text(const std::string &str)
{
    return 0;
}

void cpaf::cocoa::gui::TextBox::set_max_length(cpaf::text_range_t len)
{

}

void cpaf::cocoa::gui::TextBox::set_read_only(bool b)
{

}

bool cpaf::cocoa::gui::TextBox::is_read_only() const
{
    return false;
}
