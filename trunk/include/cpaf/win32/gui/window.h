/*!
    \file include/cpaf/win32/gui/window.h
    \brief win32 version of cpaf::api::gui::Window
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

#ifndef CPAF_WIN32_GUI_WINDOW_H
#define CPAF_WIN32_GUI_WINDOW_H

#include <cpaf/win32/gui/widget.h>
#include <cpaf/win32/gui/panel.h>
#include <cpaf/api/gui/window.h>
#include <cpaf/gui/window.h>

#include <string>

namespace cpaf {
    namespace win32 {
        namespace gui {

class Window : public virtual cpaf::win32::gui::Widget, public virtual cpaf::api::gui::Window
{
    friend LRESULT CALLBACK window_wndproc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

private:
    cpaf::win32::gui::Panel *m_root_panel;

public:
    Window() { }
    
    void create(const cpaf::gui::initializer::WindowData &params);

    int process_message(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

    cpaf::Size client_size_to_absolute(const cpaf::Size &size);

    // window interface
    virtual void set_min_content_size(const cpaf::Size&);
    virtual void set_max_content_size(const cpaf::Size&);
    virtual cpaf::Size get_min_content_size() const;
    virtual cpaf::Size get_max_content_size() const;
    virtual void set_content_panel(cpaf::api::gui::Panel *p);
    virtual boost::shared_ptr<cpaf::gui::Panel> get_content_panel() const;

    // toplevel interface
    virtual void set_title(const std::string &t);
    virtual std::string get_title();

    virtual void set_client_size(const cpaf::Size &s);
    virtual cpaf::Size get_client_size() { return cpaf::Size(); }
    virtual cpaf::Point get_client_position() { return cpaf::Point(); }
};

        } // gui
    } // win32
} // cpaf

#endif // CPAF_WIN32_GUI_WINDOW_H
