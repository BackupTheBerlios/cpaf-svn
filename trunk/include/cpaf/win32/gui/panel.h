/*!
    \file include/cpaf/win32/panel.h
    \brief win32 version of cpaf::api::gui::Panel
    \date Created: 
*/

#ifndef CPAF_WIN32_GUI_PANEL_H
#define CPAF_WIN32_GUI_PANEL_H

#include <cpaf/win32/gui/widget.h>
#include <cpaf/api/gui/panel.h>
#include <cpaf/gui/panel.h>

namespace cpaf {
    namespace win32 {
        namespace gui {

class Panel : public virtual cpaf::win32::gui::Widget, public virtual cpaf::api::gui::Panel
{
    friend LRESULT CALLBACK panel_wndproc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

public:
    Panel();
    ~Panel();

    void create(const cpaf::gui::initializer::PanelData &params);

    int process_message(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

    cpaf::gui::LayoutManager &get_layout_manager();

private:
    cpaf::gui::LayoutManager *m_layout_manager;
};

        } // gui
    } // win32
} // cpaf

#endif // CPAF_WIN32_GUI_PANEL_H
