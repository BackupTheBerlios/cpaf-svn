/*!
    \file include/cpaf/win32/gui/widget.h
    \brief win32 version of cpaf::api::gui::Widget
    \date Created: 2005-04-05
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

    Copyright (C) 2005 Robin McNeill
    http://www.snakesoft.net
    snakechomp (at) snakesoft [dot] net
*/

#ifndef CPAF_WIN32_GUI_WIDGET_H
#define CPAF_WIN32_GUI_WIDGET_H

#include <cpaf/win32/win.h>
#include <cpaf/types.h>
#include <cpaf/api/gui/widget.h>

// for initializer factory
#include <cpaf/gui/widget.h>

#include <string>

namespace cpaf {
    namespace win32 {
        namespace gui {

class Widget : public virtual cpaf::api::gui::Widget
{
private:
    bool m_delete;

protected:
    boost::weak_ptr<cpaf::gui::Widget> m_wrapper; // wrapper for this impl object
    int m_id; // unique id for the wrapper object, we send events from this
    HWND m_hwnd; // native window handle
    WNDPROC m_old_proc; // old window procedure

    cpaf::Size m_min_size, m_max_size, m_natural_size;

    Widget();

public:
    void set_old_proc(WNDPROC proc) { m_old_proc = proc; }

    /*!
        Instead of subclassing window procedures to simulate inheritance, there is only
        one window procedure, which is widget_wndproc. This function calls process_message
        which does all message processing. process_message is responsible for knowing whether or
        not to call DefWindowProc, or some other window procedure.
    */
    virtual int process_message(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

    virtual ~Widget();

    /*!
        Creates the native widget using CreateWindowEx.

        \param info         CretionInfo struct passed to the window procedure via WM_CREATE (or WM_NCCREATE)
        \param params       Initializer arguments for position, size, visibility and enabled states.
        \param parent_required If true and params.m_parent is NULL, an exception is thrown
        \param class_name   Class name passed to CreateWindowEx
        \param window_name  Window name passed to CreateWindowEx
        \param styles       Window styles
        \param styles_ex    Extended window styles
        \param x            X position
        \param y            Y position
        \param w            Width
        \param h            Height
    */
    virtual void create(const CreationInfo &info, const cpaf::gui::initializer::WidgetData &params,
        bool parent_required, LPCTSTR class_name, LPCTSTR window_name, int styles, int styles_ex = 0,
        int x = 0, int y = 0, int w = 0, int h = 0);

    cpaf::object_id get_id() const { return m_id; }
    template<typename T> boost::shared_ptr<T> get_wrapper() const;

    // object interface
    virtual void set_size(const cpaf::Size &s);
    virtual void set_min_size(const cpaf::Size &s);
    virtual void set_max_size(const cpaf::Size &s);
    virtual void set_natural_size(const cpaf::Size &s);
    virtual void set_position(const cpaf::Point &p);
    virtual void set_rect(const cpaf::Rect &r);
    virtual cpaf::Size get_size() const;
    virtual cpaf::Size get_min_size() const;
    virtual cpaf::Size get_max_size() const;
    virtual cpaf::Size get_natural_size() const;
    virtual cpaf::Point get_position() const;
    virtual cpaf::Rect get_rect() const;

    // widget interface
    virtual void *get_handle() const { return m_hwnd; }
    virtual void enable(bool e);
    virtual void show(bool show, bool focus);
    virtual bool is_enabled() const;
    virtual bool is_shown() const;
    virtual void destroy();
    virtual boost::shared_ptr<cpaf::gui::Panel> get_parent() const;
    virtual boost::shared_ptr<cpaf::gui::Window> get_parent_window() const;

protected:

    /*!
        Sets the text of this widget using SetWindowText
    */
    void set_window_text(const std::string &str);
    std::string get_window_text() const;
};

template<typename T> inline boost::shared_ptr<T> Widget::get_wrapper() const
{
    return boost::dynamic_pointer_cast<T>(m_wrapper.lock());
}

        } // gui
    } // win32
} // cpaf

#endif // CPAF_WIN32_GUI_WIDGET_H
