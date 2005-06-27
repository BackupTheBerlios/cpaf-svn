/*!
    \file include/cpaf/api/gui/window.h
    \brief Window interface declaration
    \date Created: 2005-04-05
*/

#ifndef CPAF_API_GUI_WINDOW_H
#define CPAF_API_GUI_WINDOW_H

#include <cpaf/gui/initializer/window.h>
#include <cpaf/api/gui/toplevel.h>

namespace cpaf {
    namespace api {
        namespace gui {

/*!
    \brief A Window is a top level widget which has a title bar and contains subwindows
*/
class Window : public virtual TopLevel
{
public:
    typedef cpaf::gui::initializer::WindowData data_type; //!< Initialization data used for Windows

    /*!
        \brief Constructs the native widget using the given initialization data
    */
    virtual void create(const data_type &init_params) = 0;
};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_WINDOW_H
