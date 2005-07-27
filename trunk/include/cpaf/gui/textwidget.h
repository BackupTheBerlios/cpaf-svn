/*!
    \file include/cpaf/gui/textwidget.h
    \brief cpaf::gui::TextWidget declaration
    \date Created: 2005-07-14
*/

#ifndef CPAF_GUI_TEXTWIDGET_H
#define CPAF_GUI_TEXTWIDGET_H

#include <cpaf/gui/widget.h>
#include <cpaf/gui/initializer/textwidget.h>

#include <cpaf/gui/factory.h>

namespace cpaf {
    namespace gui {

class CPAF_API TextWidget : public Widget
{
public:
    typedef cpaf::api::gui::TextWidget api_type;

    /*!
        Sets the text of the TextWidget.
    */
    void set_text(const std::string &s);

    /*!
        \return The text contained in the TextWidget.
    */
    std::string get_text() const;

    /*!
        \return The text in the requested range.
    */
    std::string get_text(const cpaf::TextRange &range) const;

    /*!
        \return The range of text that is currently selected.

        This function returns a specially formatted TextRange struct. TextRange::first is the
        selection position, and TextRange::second is the insertion point. This function does not
        gaurantee to return a normalized TextRange, meaning that first may be greater
        than second. In that case, it means that the insertion point is closer to the beginning
        of the text than the selection position.

        \remarks If the end of the text is selected, the value of length will be returned,
            not TextRange::END. If you had selected a range of text using negative ranges,
            their positive equivilants will be returned by this function.
    */
    cpaf::TextRange get_selection_range() const;

    /*!
        \brief Selects a range of text within the widget.

        This function interprets the meaning of TextRange::first and TextRange::second
        differently than other functions. TextRange::first is the "selection position"
        and TextRange::second is the "insertion point". Unlike set_selection_bounds(), this
        function lets you determine where to place the insertion point in relation to the
        selection position. This function does not normalize \a range because that would
        destroy any insertion point information relative to the selection point.

        \post The TextWidget is now focused
    */
    void set_selection_range(const cpaf::TextRange &range);

    /*!
        \brief Returns the selected range of text and whether or not there was a selection.

        \param range [out] The selected range of text is returned through this parameter.

        \remarks If the end of the text is selected, the value of length will be returned,
            not TextRange::END. If you had selected a range of text using negative ranges,
            their positive equivilants will be returned by this function.

        \note If you need to know where the insertion point is relative to the selection position,
            use get_selection_range() instead.

        \return True if there was a selection, false if not.
    */
    bool get_selection_bounds(cpaf::TextRange &range) const;

    /*!
        \brief Selects a range of text within the widget. The insertion point will
            be range.second.

        \remarks Use the value (0, TextRange::END) to select all of the text.
            A value of (N, TextRange::END) will select all of the text excluding the range [0, N).

        \post The TextWidget is now focused
    */
    void set_selection_bounds(const cpaf::TextRange &range);

    /*!
        \return The insertion point (Cursor position).
    */
    cpaf::text_range_t get_insertion_point() const;

    /*!
        \brief Sets the insertion point (Cursor position).

        \post The TextWidget is now focused
    */
    void set_insertion_point(cpaf::text_range_t pos);

    /*!
        \brief Deletes a range of text from the widget.
    */
    void delete_range(const cpaf::TextRange &range);

    /*!
        \brief Inserts text at the specified position.
    */
    void insert_text(cpaf::text_range_t pos, const std::string &str);

    /*!
        \brief Returns the number of characters in the widget.
    */
    cpaf::text_range_t get_length() const;

    /*!
        \brief Sets the maximum text length. Specify a value of -1 to indicate that
            there is no maximum text length.
    */
    void set_max_length(cpaf::text_range_t len);

    /*!
        \brief Specifies whether or not this TextWidget is read only. Users cannot modify the contents
            of read only TextWidgets.
    */
    void set_read_only(bool b);

    /*!
        \return Whether this TextWidget is in read only mode
    */
    bool is_read_only() const;

protected:
    TextWidget(api_type *impl);

private:
    api_type *m_impl;

public:
    operator api_type *() const;
    template<typename Widget> friend Widget *cpaf::gui::factory::create_widget(typename Widget::Initializer const &);
};

    } // gui
} // cpaf

#endif
