/*!
    \file src/cpaf/cocoa/textwidget.mm
    \brief Implementation of cpaf::cocoa::gui::TextWidget
    \date Created: 2005-07-14
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

#include <cpaf/cocoa/gui/textwidget.h>
#include <cpaf/exception.h>

void cpaf::cocoa::gui::TextWidget::create(const cpaf::gui::initializer::TextWidgetData &params, id widget)
{
    cpaf::cocoa::gui::Widget::create(params, widget);
    set_text(params.get_text());
}
