/*
common header for win32 implementation
*/

#ifndef CPAF_WIN32_WIN_H
#define CPAF_WIN32_WIN_H

#include <windows.h>

#include <map>

#if defined(_MSC_VER) && defined(_DEBUG)
#   include <crtdbg.h>
#   define DBG_MSG(s)      _CrtDbgReport(_CRT_WARN, __FILE__, __LINE__, "", s ## "\n");
#   define DBG_MSG_2(f, s) _CrtDbgReport(_CRT_WARN, __FILE__, __LINE__, "", f ## "\n", s);
#else
#   define DBG_MSG(s)
#   define DBG_MSG_2(f,s)
#endif

namespace cpaf {
    namespace win32 {
        namespace gui {

class Widget;

typedef std::map<HWND, cpaf::win32::gui::Widget *> WidgetMap;

//extern WidgetMap widget_map;

//template <typename T> T *get_widget_from_hwnd(HWND h)
cpaf::win32::gui::Widget *get_widget_from_hwnd(HWND h);

void widget_map_add_hwnd(HWND h, cpaf::win32::gui::Widget *wnd);
void widget_map_remove_hwnd(HWND h);

/*!
    Structure containing information passed to the window procedure through WM_CREATE.
    The reason I use this is because I cannot pass 'this' directly though lpParam of
    CreateWindowEx as a void*. Once it is recieved by the window procedure, it is a broken
    pointer unless it is assigned to a pointer of its original class. This original class is
    unknown. To avoid pointer breakage, the 'this' pointer will be passed through this struct
    which is passed through lpParam, thus preventing casting breakage. The casting breakage is
    caused by the judicious use of virtual base classes; c-style casts will not work because of them.
*/
struct CreationInfo {
    Widget *wnd; //! The object creating this window

    CreationInfo(Widget *w);
};

/*!
    This is the window procedure which is implemented outside of the win32::gui::widget classes.
    It is called by the window procedures for all widgets and contains only common functionality.
*/
LRESULT CALLBACK widget_wndproc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);


/*!
    This class wraps hooking the WM_CREATE message and is used for cpaf native widget creation.

    It hooks during ctor, and de-hooks during dtor.

    \warning Implementation of this class is not thread safe.
*/
class CreationHook
{
public:
    CreationHook();
    ~CreationHook();

    static LRESULT CALLBACK hook_proc(int code, WPARAM w_param, LPARAM l_param);
};

        } // gui
    } // win32
} // cpaf

#endif // CPAF_WIN32_WIN_H
