/*!
    \file include/cpaf/api/gui/$(NAME_LOWER).$(H_EXT)
    \brief $(NAME) interface declaration
    \date Created: $(DATE)
*/

#ifndef CPAF_API_GUI_$(NAME_UPPER)_H
#define CPAF_API_GUI_$(NAME_UPPER)_H

#include <cpaf/gui/initializer/$(NAME_LOWER).h>
#include <cpaf/api/gui/$(BASE_LOWER).h>

namespace cpaf {
    namespace api {
        namespace gui {

class $(NAME) : public virtual $(BASE)
{
public:
    typedef cpaf::gui::initializer::$(NAME)Data data_type; //!< Initialization data used for $(NAME).

    virtual void create(const data_type &init_params) = 0;
};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_$(NAME_UPPER)_H
