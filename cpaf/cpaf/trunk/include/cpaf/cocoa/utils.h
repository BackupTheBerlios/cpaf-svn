#import <Cocoa/Cocoa.h>
#include <cpaf/types.h>

namespace cpaf {
    namespace cocoa {
        namespace utils {

NSPoint convert_point(cpaf::Point p);
cpaf::Point convert_point(NSPoint p);

        } // utils
    } // cocoa
} // cpaf
