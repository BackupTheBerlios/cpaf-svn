/*
Client wrapper for api::gui::Window
*/

#ifndef CPAF_GUI_WINDOW_H
#define CPAF_GUI_WINDOW_H

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/gui/toplevel.h>
#include <cpaf/gui/factory/window.h>

namespace cpaf {
    namespace gui {

/*!
    \brief A Window is a top level widget that contains a title bar, min max and close buttons,
    and contains subwindows.
*/
class CPAF_API Window : public TopLevel
{
public:
    /*!
        Factory for creating window objects
    */
    class CPAF_API Factory : public cpaf::gui::factory::Window<Factory>
    {
    public:
        Factory();

        template <typename T> T *create() const
        {
            return dynamic_cast<T*>(create(new T));
        }

        Window *create() const
        {
            return create(new Window);
        }

    protected:
        /*!
            This function creates a native widget and uses \a w to wrap it.

            \return The initialized wrapper w.
        */
        cpaf::gui::Window *create(cpaf::gui::Window *w) const;
    };

private:
    // not shared_ptr because this object will never be responsible for deleting this pointer
    // it only serves to save extraneous casting in source
    cpaf::api::gui::Window *m_impl;

protected:
    Window();
    void set_impl(cpaf::api::gui::Window *impl);

public:
    operator cpaf::api::gui::Window *();
};

    } // gui
} // cpaf

#endif // CPAF_GUI_WINDOW_H
