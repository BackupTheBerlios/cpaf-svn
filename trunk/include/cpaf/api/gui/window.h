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
    namespace gui { class Panel; }
    namespace api {
        namespace gui {

class Panel;

class Window : public virtual TopLevel
{
public:
    typedef cpaf::gui::initializer::WindowData data_type; //!< Initialization data used for Windows

    virtual void create(const data_type &init_params) = 0;

    virtual void set_content_panel(cpaf::api::gui::Panel *p) = 0;
    virtual boost::shared_ptr<cpaf::gui::Panel> get_content_panel() const = 0;
};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_WINDOW_H
