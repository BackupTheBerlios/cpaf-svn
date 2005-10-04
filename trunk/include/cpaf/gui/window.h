/*!
    \file include/cpaf/gui/window.h
    \brief cpaf::gui::Window declaration
    \date Created: 2005-04-05
*/

#ifndef CPAF_GUI_WINDOW_H
#define CPAF_GUI_WINDOW_H

#include <cpaf/gui/toplevel.h>
#include <cpaf/gui/initializer/window.h>

namespace cpaf {
    namespace gui {

/*!
    \brief A Window is a top level widget which has a title bar and contains subwindows
*/
class CPAF_API Window : public TopLevel
{
public:
    typedef cpaf::api::gui::Window api_type;
    typedef WindowInitializer Initializer;

    /*!
        Creates a Window
    */
    static boost::shared_ptr<Window> create(const Initializer &initializer);

    /*!
        Sets the content panel for this window
    */
    void set_content_panel(cpaf::gui::Panel *p);

    /*!
        \return This window's content panel
    */
    cpaf::gui::Panel *get_content_panel() const;

private:
    api_type *m_impl;

protected:
    Window();
    Window(api_type *impl);

    /*!
        \brief Constructs the native widget using the given initialization data
    */
    boost::shared_ptr<Window> initialize(const Initializer &initializer);

public:
    api_type *get_impl() const;
};

    } // gui
} // cpaf



#endif // CPAF_GUI_WINDOW_H
