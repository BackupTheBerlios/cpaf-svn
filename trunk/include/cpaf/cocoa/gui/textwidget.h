/*!
    \file include/cpaf/cocoa/textwidget.h
    \brief Cocoa version of cpaf::api::gui::TextWidget
    \date Created: 2005-07-14
*/

#ifndef CPAF_COCOA_GUI_TEXTWIDGET_H
#define CPAF_COCOA_GUI_TEXTWIDGET_H

#include <cpaf/cocoa/gui/widget.h>
#include <cpaf/api/gui/textwidget.h>
#include <cpaf/gui/textwidget.h>

#include <string>

namespace cpaf {
    namespace cocoa {
        namespace gui {

class TextWidget : public virtual cpaf::cocoa::gui::Widget, public virtual cpaf::api::gui::TextWidget
{
public:
    TextWidget() { }

    void create(const cpaf::gui::initializer::TextWidgetData &params, id widget);

    virtual void set_text(const std::string &s) = 0;
    virtual std::string get_text() const = 0;
    virtual std::string get_text(const cpaf::TextRange &range) const = 0;
    virtual cpaf::text_range_t get_length() const = 0;

    virtual cpaf::TextRange get_selection_range() const = 0;
    virtual void set_selection_range(const cpaf::TextRange &range) = 0;
    virtual bool get_selection_bounds(cpaf::TextRange &range) const = 0;
    virtual void set_selection_bounds(const cpaf::TextRange &range) = 0;

    virtual cpaf::text_range_t get_insertion_point() const = 0;
    virtual void set_insertion_point(cpaf::text_range_t pos) = 0;

    virtual void delete_range(const cpaf::TextRange &range) = 0;
    virtual cpaf::text_range_t insert_text(const std::string &str, cpaf::text_range_t pos) = 0;
    virtual cpaf::text_range_t insert_text(const std::string &str) = 0;

    virtual void set_max_length(cpaf::text_range_t len) = 0;

    virtual void set_read_only(bool b) = 0;
    virtual bool is_read_only() const = 0;
};

        } // gui
    } // cocoa
} // cpaf

#endif
