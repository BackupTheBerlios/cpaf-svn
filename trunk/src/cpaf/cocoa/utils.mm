#include <cpaf/cocoa/utils.h>

//! \todo test that on a dual-screen.

NSPoint cpaf::cocoa::utils::convert_point(cpaf::Point p)
{
    return NSMakePoint(p.x, [[NSScreen mainScreen] frame].size.height-p.y);
}

cpaf::Point cpaf::cocoa::utils::convert_point(NSPoint p)
{
    return cpaf::Point(p.x, [[NSScreen mainScreen] frame].size.height-p.y);
}