/*!
    \file src/cpaf/types.cpp
    \brief Implementation of basic cpaf types
    \date Created: 2005-04-05
*/

/*
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
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
