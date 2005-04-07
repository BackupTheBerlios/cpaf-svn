/*
Common structure definitions
*/

#ifndef _CPAF_DEFS_H_
#define _CPAF_DEFS_H_

namespace cpaf {

struct Size
{
    int width, height;

    Size()
        : width(0),
        height(0)
    { }

    Size(int w, int h)
        : width(w),
        height(h)
    { }
};

struct Point
{
    int x, y;

    Point()
        : x(0),
        y(0)
    { }

    Point(int xx, int yy)
        : x(xx),
        y(yy)
    { }
};

} // namespace cpaf

#endif // _CPAF_DEFS_H_
