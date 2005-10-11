/*!
    \file src/cpaf/cocoa/panel.mm
    \brief Implementation of cpaf::cocoa::gui::Panel
    \date Created: 2005-08-08
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

#include <cpaf/cocoa/gui/panel.h>
#include <cpaf/exception.h>

using namespace cpaf::cocoa::gui;

CPAF_COCOA_INTERFACE(View)
CPAF_COCOA_IMPLEMENTATION(View)

void Panel::create(const cpaf::gui::initializer::PanelData &params)
{
    m_layout_manager = params.get_layout_manager();
    if( !m_layout_manager )
        throw cpaf::Exception(cpaf::Exception::PANEL_NO_LAYOUT_MANAGER, __LINE__, __FILE__);

    Widget::create(params, [[CpafView alloc] init]);

    send_event(cpaf::event::WIDGET_CREATE);
}

void Panel::destroy()
{
  NSWindow *window = [m_object window];

  // Are we the content view of a window?
  if ([window contentView] == m_object)
  {
      // Then set up a dummy content view, so we don't crash
      [window setContentView:[[[NSView alloc] init] autorelease]];
  }

  Widget::destroy();
}
