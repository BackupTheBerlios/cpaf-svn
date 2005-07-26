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
