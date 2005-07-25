/*!
    \file src/cpaf/types.cpp
    \brief Implementation of basic cpaf types
    \date Created: 2005-04-05
*/

#include <cpaf/types.h>

using cpaf::Size;
using cpaf::Point;

const cpaf::text_range_t cpaf::TextRange::END = std::numeric_limits<text_range_t>::max();

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
