/*!
    \file include/cpaf/api/gui/textwidget.h
    \brief TextWidget interface declaration
    \date Created: 2005-07-14
*/

#ifndef CPAF_API_GUI_TEXTWIDGET_H
#define CPAF_API_GUI_TEXTWIDGET_H

#include <cpaf/gui/initializer/textwidget.h>
#include <cpaf/api/gui/widget.h>

#include <string>

namespace cpaf {
    namespace api {
        namespace gui {

class TextWidget : public virtual Widget
{
public:
    typedef cpaf::gui::initializer::TextWidgetData data_type; //!< Initialization data used for TextWidgets.

    virtual void set_text(const std::string &s) = 0;
    virtual std::string get_text() = 0;
    virtual std::string get_text(const cpaf::TextRange &range) = 0;
    virtual cpaf::text_range_t get_length() = 0;

    virtual cpaf::TextRange get_selection_range() = 0;
    virtual void set_selection_range(const cpaf::TextRange &range) = 0;
    virtual bool get_selection_bounds(cpaf::TextRange &range) = 0;
    virtual void set_selection_bounds(const cpaf::TextRange &range) = 0;

    virtual cpaf::text_range_t get_insertion_point() = 0;
    virtual void set_insertion_point(cpaf::text_range_t pos) = 0;

    virtual void delete_range(const cpaf::TextRange &range) = 0;
    virtual void insert_text(cpaf::text_range_t pos, const std::string &str) = 0;

    virtual void set_max_length(cpaf::text_range_t len) = 0;

    virtual void set_read_only(bool b) = 0;
    virtual bool is_read_only() = 0;
};

        } // gui
    } // api
} // cpaf

#endif
