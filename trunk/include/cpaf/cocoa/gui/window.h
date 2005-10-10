/**
 * \file include/cpaf/cocoa/gui/window.h
 * \brief Cocoa version of api::Window
 * \date Created: 2005-04-29
 */

#ifndef CPAF_COCOA_GUI_WINDOW_H
#define CPAF_COCOA_GUI_WINDOW_H

#include <cpaf/api/gui/window.h>
#include <cpaf/cocoa/gui/widget.h>
#include <cpaf/cocoa/gui/panel.h>
#include <cpaf/types.h>

#include <string>

namespace cpaf {
    namespace cocoa {
        namespace gui {

class Window : public virtual cpaf::cocoa::gui::Widget, public virtual cpaf::api::gui::Window
{
private:
    cpaf::cocoa::gui::Panel *m_root_panel;
public:
    Window() { };

    void create(const cpaf::gui::initializer::WindowData &params);

    // object interface
    virtual void set_size(const cpaf::Size&);
    virtual void set_min_size(const cpaf::Size&);
    virtual void set_max_size(const cpaf::Size&);
    virtual void set_position(const cpaf::Point&);
    virtual cpaf::Size get_size() const;
    virtual cpaf::Size get_min_size() const;
    virtual cpaf::Size get_max_size() const;
    virtual cpaf::Point get_position() const;

    // widget interface
    virtual void enable(bool sensitive) { } //! \todo
    virtual bool is_enabled() { return false; }  //! \todo
    virtual bool is_shown() { return false; }  //! \todo
    virtual void show(bool show, bool activate);

    // toplevel interface
    virtual void set_title(const std::string&);
    virtual std::string get_title();

    virtual void set_client_size(const cpaf::Size&);
    virtual cpaf::Size get_client_size();
    virtual cpaf::Point get_client_position();

    virtual void set_content_panel(cpaf::api::gui::Panel *p);
    virtual boost::shared_ptr<cpaf::gui::Panel> get_content_panel() const;
};

        } // gui
    } // cocoa
} // cpaf

#endif // CPAF_COCOA_GUI_WINDOW_H
