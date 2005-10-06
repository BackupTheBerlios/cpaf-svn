/**
 * \file include/cpaf/cocoa/utils.mm
 * \brief Cocoa utilities
 * \date Created: 2005-05-05
 */
 
#include <cpaf/cocoa/utils.h>

// Converting cpaf::point <-> NSPoint
//! \todo test that on a dual-screen.

NSPoint cpaf::cocoa::utils::convert_point(cpaf::Point p)
{
    return NSMakePoint(p.x, [[NSScreen mainScreen] frame].size.height-p.y);
}

cpaf::Point cpaf::cocoa::utils::convert_point(NSPoint p)
{
    return cpaf::Point(p.x, [[NSScreen mainScreen] frame].size.height-p.y);
}


// Converting cpaf::TextRange <-> NSRange

NSRange cpaf::cocoa::utils::convert_range(cpaf::TextRange r, int length)
{
    // Check, whether the range is within the length
    // Double check for < 0 (when length is too negative)

    if (r.first < 0)
        r.first = length + r.first;
    if (r.first < 0)
        r.first = 0;
    if (r.first > length)
        r.first = length;
    
    if (r.second < 0)
        r.second = length + r.second;
    if (r.second < 0)
        r.second = 0;
    if (r.second > length)
        r.second = length;
    
    // Normalize it, so r.second > s.first
    r.normalize();
    
    // Finally return the range
    return NSMakeRange(r.first, r.second-r.first);
}
