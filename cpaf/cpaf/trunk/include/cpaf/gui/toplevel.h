/*
Client wrapper for api::gui::TopLevel
this object is not createable by client code
*/

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/gui/widget.h>

// would rather not need this but no way around it right now
#include <string>

namespace cpaf {
    namespace gui {

class CPAF_EXP TopLevel : public Widget
{
private:
    // not shared_ptr because this object will never be responsible for deleting this pointer
    // it only serves to save extraneous casting in source
    cpaf::api::gui::TopLevel *m_impl;

protected:
    TopLevel(const cpaf::api::gui::TopLevelPtr &p);

public:
    void set_title(const std::string &t);
    std::string get_title();
};

    } // gui
} // cpaf
