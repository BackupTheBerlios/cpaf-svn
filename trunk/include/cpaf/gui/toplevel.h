/*!
    \file include/cpaf/gui/toplevel.h
    \brief cpaf::gui::TopLevel declaration
    \date Created: 2005-04-05
*/

#ifndef CPAF_GUI_TOPLEVEL_H
#define CPAF_GUI_TOPLEVEL_H

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/gui/widget.h>

// would rather not need this but no way around it right now
#include <string>

namespace cpaf {
    namespace gui {

class CPAF_API TopLevel : public Widget
{
public:
    typedef cpaf::api::gui::TopLevel api_type;

    void show(bool show = true, bool focus = true);

    void set_title(const std::string &t);
    std::string get_title();

    void set_client_size(const cpaf::Size &s);
    cpaf::Size get_client_size();
    cpaf::Point get_client_position();

private:
    // not shared_ptr because this object will never be responsible for deleting this pointer
    // it only serves to save extraneous casting in source
    cpaf::api::gui::TopLevel *m_impl;

protected:
    TopLevel(cpaf::api::gui::TopLevel *impl);

public:
    ~TopLevel();
    operator cpaf::api::gui::TopLevel *();
};

    } // gui
} // cpaf

#endif // CPAF_GUI_TOPLEVEL_H
