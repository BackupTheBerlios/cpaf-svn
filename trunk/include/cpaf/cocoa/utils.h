/**
 * \file include/cpaf/cocoa/utils.h
 * \brief Cocoa utilities
 * \date Created: 2005-05-05
 */

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
