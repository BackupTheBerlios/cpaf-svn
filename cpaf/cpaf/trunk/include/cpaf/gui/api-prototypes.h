/*
cpaf::api::gui namespace prototypes for use by gui::foo headers
*/

#include <boost/shared_ptr.hpp>

namespace cpaf {
    namespace api {
        namespace gui {
            class Sizeable;
            typedef boost::shared_ptr<cpaf::api::gui::Sizeable> SizeablePtr;
            class Widget;
            typedef boost::shared_ptr<cpaf::api::gui::Widget> WidgetPtr;
            class TopLevel;
            typedef boost::shared_ptr<cpaf::api::gui::TopLevel> TopLevelPtr;
            class Window;
            typedef boost::shared_ptr<cpaf::api::gui::Window> WindowPtr;
            class Sizer;
            typedef boost::shared_ptr<cpaf::api::gui::Sizer> SizerPtr;
        } // gui
    } // api
} // cpaf
