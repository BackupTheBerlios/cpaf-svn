/*!
    \file include/cpaf/$(PORT_LOWER)/$(NAME_LOWER).$(H_EXT)
    \brief $(PORT) version of cpaf::api::gui::$(NAME)
    \date Created: $(DATE)
*/

#ifndef CPAF_$(PORT_UPPER)_GUI_$(NAME_UPPER)_H
#define CPAF_$(PORT_UPPER)_GUI_$(NAME_UPPER)_H

#include <cpaf/$(PORT_LOWER)/gui/$(BASE_LOWER).h>
#include <cpaf/api/gui/$(NAME_LOWER).h>
#include <cpaf/gui/$(NAME_LOWER).h>

namespace cpaf {
    namespace $(PORT_LOWER) {
        namespace gui {

class $(NAME) : public virtual cpaf::$(PORT_LOWER)::gui::$(BASE), public virtual cpaf::api::gui::$(NAME)
{
public:
$(IF CONSTRUCTABLE)
    void create(const cpaf::gui::initializer::$(NAME)Data &params);
$(END)
};

        } // gui
    } // $(PORT_LOWER)
} // cpaf

#endif // CPAF_$(PORT_UPPER)_GUI_$(NAME_UPPER)_H
