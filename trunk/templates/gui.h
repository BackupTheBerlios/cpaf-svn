/*!
    \file include/cpaf/gui/$(NAME_LOWER).$(H_EXT)
    \brief cpaf::gui::$(NAME) declaration
    \date Created: $(DATE)
*/

#ifndef CPAF_GUI_$(NAME_UPPER)_H
#define CPAF_GUI_$(NAME_UPPER)_H

#include <cpaf/gui/$(BASE_LOWER).h>
#include <cpaf/gui/initializer/$(NAME_LOWER).h>

namespace cpaf {
    namespace gui {

class CPAF_API $(NAME) : public $(BASE)
{
public:
    typedef cpaf::api::gui::$(NAME) api_type;
    typedef $(NAME)Initializer Initializer;

$(IF CONSTRUCTABLE)
    static boost::shared_ptr<$(NAME)> create(const Initializer &initializer);
$(END)

private:
    api_type *m_impl;

protected:
$(IF CONSTRUCTABLE)
    $(NAME)();
$(END)
    $(NAME)(api_type *impl);

$(IF CONSTRUCTABLE)
    /*!
        \brief Constructs the native widget using the given initializer
    */
    boost::shared_ptr<$(NAME)> initialize(const Initializer &initializer);
$(END)

public:
    api_type *get_impl() const;
};

    } // gui
} // cpaf

#endif // CPAF_GUI_$(NAME_UPPER)_H
