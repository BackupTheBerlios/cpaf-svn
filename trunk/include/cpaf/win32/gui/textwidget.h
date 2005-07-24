/*!
    \file include/cpaf/win32/textwidget.h
    \brief win32 version of cpaf::api::gui::TextWidget
    \date Created: 2005-07-17
*/

#ifndef CPAF_WIN32_GUI_TEXTWIDGET_H
#define CPAF_WIN32_GUI_TEXTWIDGET_H

#include <cpaf/win32/gui/widget.h>
#include <cpaf/api/gui/textwidget.h>
#include <cpaf/gui/textwidget.h>

#include <string>

namespace cpaf {
    namespace win32 {
        namespace gui {

class TextWidget : public virtual cpaf::win32::gui::Widget, public virtual cpaf::api::gui::TextWidget
{
public:
    virtual void set_text(const std::string &s);
    virtual std::string get_text();
    virtual std::string get_text(const cpaf::TextRange &range);
    virtual cpaf::text_range_t get_length();

    virtual cpaf::TextRange get_selection_range();
    virtual void set_selection_range(const cpaf::TextRange &range);
    virtual bool get_selection_bounds(cpaf::TextRange &range);
    virtual void set_selection_bounds(const cpaf::TextRange &range);

    virtual cpaf::text_range_t get_insertion_point();
    virtual void set_insertion_point(cpaf::text_range_t pos);

    virtual void delete_range(const cpaf::TextRange &range);
    virtual void insert_text(cpaf::text_range_t pos, const std::string &str);

    virtual void set_max_length(cpaf::text_range_t len);

    virtual void set_read_only(bool b);
    virtual bool is_read_only();
};

        } // gui
    } // win32
} // cpaf

#endif
