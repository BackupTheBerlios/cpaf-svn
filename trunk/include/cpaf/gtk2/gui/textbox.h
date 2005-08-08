/**
 * \file include/cpaf/gtk2/textbox.h
 * \brief Gtk2 version of cpaf::api::gui::TextBox
 * \date Created: 2005-07-08
 */

#ifndef CPAF_GTK2_GUI_TEXTBOX_H
#define CPAF_GTK2_GUI_TEXTBOX_H

#include <cpaf/gtk2/gui/widget.h>
#include <cpaf/api/gui/textbox.h>
#include <cpaf/gui/textbox.h>

#include <string>

namespace cpaf {
    namespace gtk2 {
        namespace gui {

class TextBox : public virtual cpaf::gtk2::gui::Widget, public virtual cpaf::api::gui::TextBox
{
public:
    TextBox() { }

    void create(const cpaf::gui::initializer::TextBoxData &params);

    virtual void set_text(const std::string&);
    virtual std::string get_text() const;

    virtual std::string get_text(const cpaf::TextRange &range) const {return "";}
    virtual cpaf::text_range_t get_length() const {return 0;}

    virtual cpaf::TextRange get_selection_range() const {return cpaf::TextRange();}
    virtual void set_selection_range(const cpaf::TextRange &range) {}
    virtual bool get_selection_bounds(cpaf::TextRange &range) const {return false;}
    virtual void set_selection_bounds(const cpaf::TextRange &range) {}

    virtual cpaf::text_range_t get_insertion_point() const {return 0;}
    virtual void set_insertion_point(cpaf::text_range_t pos) {}

    virtual void delete_range(const cpaf::TextRange &range) {}
    virtual void insert_text(cpaf::text_range_t pos, const std::string &str) {}

    virtual void set_max_length(cpaf::text_range_t len) {}

    virtual void set_read_only(bool b) {}
    virtual bool is_read_only() const {return false;}
};

        } // gui
    } // gtk2
} // cpaf

#endif // CPAF_GTK2_GUI_TEXTBOX_H
