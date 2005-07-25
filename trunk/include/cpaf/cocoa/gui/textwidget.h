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

    virtual void set_text(const std::string &s);
    virtual std::string get_text() const;
    virtual std::string get_text(const cpaf::TextRange &range) const;
    virtual cpaf::text_range_t get_length() const;

    virtual cpaf::TextRange get_selection_range() const;
    virtual void set_selection_range(const cpaf::TextRange &range);
    virtual bool get_selection_bounds(cpaf::TextRange &range) const;
    virtual void set_selection_bounds(const cpaf::TextRange &range);

    virtual cpaf::text_range_t get_insertion_point() const;
    virtual void set_insertion_point(cpaf::text_range_t pos);

    virtual void delete_range(const cpaf::TextRange &range);
    virtual void insert_text(cpaf::text_range_t pos, const std::string &str);

    virtual void set_max_length(cpaf::text_range_t len);

    virtual void set_read_only(bool b);
    virtual bool is_read_only() const;
};

        } // gui
    } // cocoa
} // cpaf

#endif
