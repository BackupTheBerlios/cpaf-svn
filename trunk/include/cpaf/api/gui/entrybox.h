/*!
    \file include/cpaf/api/gui/entrybox.h
    \brief EntryBox interface declaration
    \date Created: 2005-07-14
*/

#ifndef CPAF_API_GUI_ENTRYBOX_H
#define CPAF_API_GUI_ENTRYBOX_H

#include <cpaf/gui/initializer/entrybox.h>
#include <cpaf/api/gui/textwidget.h>

#include <string>

namespace cpaf {
    namespace api {
        namespace gui {

class EntryBox : public virtual TextWidget
{
public:
    typedef cpaf::gui::initializer::EntryBoxData data_type; //!< Initialization data used for EntryBoxes.

    virtual void create(const data_type &init_params) = 0;
};

        } // gui
    } // api
} // cpaf

#endif
