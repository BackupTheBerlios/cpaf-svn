/*
cpaf::api::gui namespace prototypes for use by gui::foo headers
*/

#ifndef CPAF_GUI_API_PROTOTYPES_H
#define CPAF_GUI_API_PROTOTYPES_H

//#include <boost/shared_ptr.hpp>

namespace cpaf {
    namespace api {
        namespace gui {
            class Object;
            //typedef boost::shared_ptr<cpaf::api::gui::Object> ObjectPtr;
            class Widget;
            //typedef boost::shared_ptr<cpaf::api::gui::Widget> WidgetPtr;
            class TopLevel;
            //typedef boost::shared_ptr<cpaf::api::gui::TopLevel> TopLevelPtr;
            class Window;
            //typedef boost::shared_ptr<cpaf::api::gui::Window> WindowPtr;
            class Sizer;
            //typedef boost::shared_ptr<cpaf::api::gui::Sizer> SizerPtr;
            class Button;
        } // gui
    } // api
} // cpaf

#endif // CPAF_GUI_API_PROTOTYPES_H