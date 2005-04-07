/*
Common structure definitions
*/

#ifndef CPAF_DEFS_H
#define CPAF_DEFS_H

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

#endif // CPAF_DEFS_H
