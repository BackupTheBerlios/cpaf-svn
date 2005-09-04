/*!
    \file include/cpaf/win32/win.h
    \brief Declarations for various win32 port stuff
    \date Created: 2005-04-05
*/

#ifndef CPAF_WIN32_WIN_H
#define CPAF_WIN32_WIN_H

#define NOMINMAX
#include <windows.h>

#include <cpaf/debug.h>

#include <map>
#include <stack>

namespace cpaf {
    namespace win32 {
        namespace gui {

class Widget;

Widget *get_widget_from_hwnd(HWND h);
template <typename T> T *get_widget_from_hwnd(HWND h)
{
    return dynamic_cast<T*>(get_widget_from_hwnd(h));
}
/*!
    Associate a Widget pointer with a HWND
*/
void associate_hwnd(HWND h, Widget *wnd);

/*!
    Disasociate a Widget pointer from a HWND
*/
void disassociate_hwnd(HWND h);

/*!
    Returns true if no more widgets exist.
    This is used to determine when an application should terminate.
    Win32 applications terminate when there are no native widgets.
*/
bool has_widgets();

typedef std::stack<Widget*> WidgetDeletionStack;

/*!
    Adds a widget to the deletion stack
*/
void widget_deletion_stack_push(Widget *w);

/*!
    Deletes the widget on the top of the stack
*/
void widget_deletion_stack_pop();

/*!
    Returns true if there are widgets in the deletion stack waiting to be deleted
*/
bool widget_deletion_stack_waiting();

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

    It hooks during ctor.

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
