/**
 * \file src/cpaf/gtk2/textbox.cpp
 * \brief Implementation of cpaf::gtk2::gui::TextBox
 * \date Created: 2005-07-08
*/

#include <cpaf/gtk2/gui/textbox.h>
#include <cpaf/gtk2/gui/panel.h>
#include <cpaf/exception.h>
#include <cpaf/event/event.h>

#include <gtk/gtk.h>

using namespace cpaf::gtk2::gui;

extern "C" {
static void
cpaf_text_buffer_changed(GtkTextBuffer * gtktextbuffer,
                         TextBox * widget)
{
    widget->send_event(cpaf::event::TEXT_CHANGED);
}
} // extern "C"

void
TextBox::create (const cpaf::gui::initializer::TextBoxData &params)
{
    //! \todo Use factory params
    Widget::create (params, gtk_scrolled_window_new (NULL, NULL));

    //! \todo Use correct border
    gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (m_widget),
                                         GTK_SHADOW_IN);

    m_text = gtk_text_view_new ();
    gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (m_text), GTK_WRAP_WORD_CHAR);
    m_buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (m_text));

    g_signal_connect (m_buffer, "changed",
                      G_CALLBACK (cpaf_text_buffer_changed),
                      this);

    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (m_widget),
                                    GTK_POLICY_AUTOMATIC,
                                    GTK_POLICY_AUTOMATIC);

    gtk_container_add (GTK_CONTAINER (m_widget), m_text);

    gtk_widget_show (m_text);

    cpaf::gui::Panel *parent = params.get_parent();
    if (parent)
    {
        GtkFixed * hparent = GTK_FIXED (parent->get_handle());
        gtk_fixed_put (hparent,
                       m_widget,
                       params.get_pos().x,
                       params.get_pos().y);
    }
    else
        throw cpaf::Exception (cpaf::Exception::WIDGET_NO_PARENT, __LINE__, __FILE__);

    if (!params.get_text().empty())
        set_text (params.get_text());

    /*!
        \note Show is always last - it might realize the widget (if params.m_show == true),
        and we don't want that to happen before all other data is set.
     */
    if (params.get_show())
        show (true, params.get_activate());
}

void
TextBox::set_text (const std::string &str)
{
    //! \todo std::string -> UTF8
    gtk_text_buffer_set_text (m_buffer, str.c_str(), str.length());
}

std::string
TextBox::get_text () const
{
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds (m_buffer, &start, &end);
    //! \note Can we do this with a shared pointer somehow?
    gchar * text = gtk_text_buffer_get_text (m_buffer, &start, &end, TRUE);
    //! \todo UTF8 -> std::string
    std::string ret(text);
    g_free (text);
    return ret;
}

std::string
TextBox::get_text (const cpaf::TextRange &r) const
{
    cpaf::TextRange range(r);
    range.normalize (gtk_text_buffer_get_char_count (m_buffer));

    GtkTextIter start, end;

    //! \note What happens if both args are END?
    if (range.second == cpaf::TextRange::END)
        gtk_text_buffer_get_end_iter (m_buffer, &end);
    else
        gtk_text_buffer_get_iter_at_offset (m_buffer, &end, range.second);

    gtk_text_buffer_get_iter_at_offset (m_buffer, &start, range.first);

    //! \note Can we do this with a shared pointer somehow?
    gchar * text = gtk_text_buffer_get_text (m_buffer, &start, &end, TRUE);
    //! \todo UTF8 -> std::string
    std::string ret(text);
    g_free (text);
    return ret;
}

cpaf::text_range_t
TextBox::get_length () const
{
    return gtk_text_buffer_get_char_count (m_buffer);
}

cpaf::TextRange
TextBox::get_selection_range () const
{
    GtkTextIter select_pos, insert_pos;

    gtk_text_buffer_get_iter_at_mark (m_buffer,
                                      &select_pos,
                                      gtk_text_buffer_get_selection_bound (m_buffer));
    gtk_text_buffer_get_iter_at_mark (m_buffer,
                                      &insert_pos,
                                      gtk_text_buffer_get_insert (m_buffer));
    return cpaf::TextRange (gtk_text_iter_get_offset (&select_pos),
                            gtk_text_iter_get_offset (&insert_pos));
}

void
TextBox::set_selection_range (const cpaf::TextRange &range)
{
    GtkTextIter select_pos, insert_pos;

    gtk_widget_grab_focus (m_text);

    gtk_text_buffer_get_iter_at_offset (m_buffer, &select_pos, range.first);
    gtk_text_buffer_get_iter_at_offset (m_buffer, &insert_pos, range.second);
    gtk_text_buffer_select_range (m_buffer, &insert_pos, &select_pos);
}

bool
TextBox::get_selection_bounds (cpaf::TextRange &range) const
{
    GtkTextIter start, end;
    bool ret;

    ret = gtk_text_buffer_get_selection_bounds (m_buffer, &start, &end);
    range.first = gtk_text_iter_get_offset (&start);
    range.second = gtk_text_iter_get_offset (&end);
    return ret;
}

void
TextBox::set_selection_bounds (const cpaf::TextRange &range)
{
    //! \todo Do we need to normalize?

    set_selection_range (range);
}

cpaf::text_range_t
TextBox::get_insertion_point () const
{
    GtkTextIter insert_pos;
    gtk_text_buffer_get_iter_at_mark (m_buffer,
                                      &insert_pos,
                                      gtk_text_buffer_get_insert (m_buffer));
    return gtk_text_iter_get_offset (&insert_pos);
}

void
TextBox::set_insertion_point (cpaf::text_range_t pos)
{
    GtkTextIter where;
    //! \todo Should the focusing postcondition remain in effect?
    gtk_widget_grab_focus (m_text);
    gtk_text_buffer_get_iter_at_offset (m_buffer, &where, pos);
    gtk_text_buffer_place_cursor (m_buffer, &where);
}

void
TextBox::delete_range (const cpaf::TextRange &r)
{
    cpaf::TextRange range(r);
    range.normalize (gtk_text_buffer_get_char_count (m_buffer));

    GtkTextIter start, end;

    //! \note What happens if both args are END?
    if (range.second == cpaf::TextRange::END)
        gtk_text_buffer_get_end_iter (m_buffer, &end);
    else
        gtk_text_buffer_get_iter_at_offset (m_buffer, &end, range.second);

    gtk_text_buffer_get_iter_at_offset (m_buffer, &start, range.first);

    gtk_text_buffer_delete (m_buffer, &start, &end);
}

cpaf::text_range_t
TextBox::insert_text (const std::string &str,
                      cpaf::text_range_t pos)
{
    //! \todo Do we allow negative positions? If not, remove the if block
    if (pos < 0)
        pos += gtk_text_buffer_get_char_count (m_buffer);

    GtkTextIter iter;

    if (pos == cpaf::TextRange::END)
        gtk_text_buffer_get_end_iter (m_buffer, &iter);
    else
        gtk_text_buffer_get_iter_at_offset (m_buffer, &iter, pos);

    //! \todo std::string -> UTF8
    gtk_text_buffer_insert (m_buffer, &iter, str.c_str(), str.length());

    //! \todo return new pos
    return 0;
}

cpaf::text_range_t
TextBox::insert_text (const std::string &str)
{
    //! \todo IMPLEMENT
    return 0;
}

void
TextBox::set_max_length (cpaf::text_range_t len)
{
    //! \todo IMPLEMENT
}

void
TextBox::set_read_only (bool b)
{
    gtk_text_view_set_editable (GTK_TEXT_VIEW (m_widget), !b);
}

bool
TextBox::is_read_only () const
{
    return !gtk_text_view_get_editable (GTK_TEXT_VIEW (m_widget));
}
