/*
Implementation for basic cpaf types
*/

#include <cpaf/types.h>

using cpaf::Size;
using cpaf::Point;

Size cpaf::operator+(const Size &l, const Size &r)
{
    return Size(l.width + r.width, l.height + r.height);
}

Size cpaf::operator-(const Size &l, const Size &r)
{
    return Size(l.width - r.width, l.height - r.height);
}

Size cpaf::operator*(const Size &l, float f)
{
    return Size(l.width * f, l.height * f);
}

Size cpaf::operator/(const Size &l, float f)
{
    return Size(l.width * f, l.height * f);
}

Point cpaf::operator+(const Point &l, const Point &r)
{
    return Point(l.x + r.x, l.y + r.y);
}

Point cpaf::operator-(const Point &l, const Point &r)
{
    return Point(l.x - r.x, l.y - r.y);
}
