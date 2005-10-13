/*!
    \file include/cpaf/api/gui/textwidget.h
    \brief TextWidget interface declaration
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
    } // api
} // cpaf

#endif
