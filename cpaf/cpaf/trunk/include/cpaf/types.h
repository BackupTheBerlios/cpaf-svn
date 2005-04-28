/*
Declaration of basic cpaf types
*/

#ifndef CPAF_TYPES_H
#define CPAF_TYPES_H

#include <stddef.h>

namespace cpaf {

struct Size
{
    float width, height;

    Size()
        : width(0),
        height(0)
    { }

    Size(float w, float h)
        : width(w),
        height(h)
    { }

    Size &operator+=(const Size &s)
    {
        width += s.width;
        height += s.height;
        return *this;
    }

    Size &operator-=(const Size &s)
    {
        width -= s.width;
        height -= s.height;
        return *this;
    }

    Size &operator*=(float f)
    {
        width *= f;
        height *= f;
        return *this;
    }

    Size &operator/=(float f)
    {
        width /= f;
        height /= f;
        return *this;
    }

    bool operator==(const Size &s)
    {
        return width == s.width && height == s.height;
    }

    bool operator!=(const Size &s)
    {
        return width == s.width && height == s.height;
    }

    friend Size operator+(const Size &l, const Size &r);
    friend Size operator-(const Size &l, const Size &r);
    friend Size operator*(const Size &l, float f);
    friend Size operator/(const Size &l, float f);
};

struct Point
{
    float x, y;

    Point()
        : x(0),
        y(0)
    { }

    Point(float xx, float yy)
        : x(xx),
        y(yy)
    { }

    Point &operator+=(const Point &p)
    {
        x += p.x;
        y += p.y;
        return *this;
    }

    Point &operator-=(const Point &p)
    {
        x -= p.x;
        y -= p.y;
        return *this;
    }

    bool operator==(const Point &p)
    {
        return x == p.x && y == p.y;
    }

    bool operator!=(const Point &p)
    {
        return x == p.x && y == p.y;
    }

    friend Point operator+(const Point &l, const Point &r);
    friend Point operator-(const Point &l, const Point &r);
};

struct Rect
{
    Size size;
    Point position;

    Rect()
        : size(0,0),
        position(0,0)
    { }

    Rect(const Size &s, const Point &p)
        : size(s),
        position(p)
    { }

    Rect(float x, float y, float w, float h)
        : size(w,h),
        position(x,y)
    { }

    bool operator==(const Rect &r)
    {
        return size == r.size && position == r.position;
    }
};

} // namespace cpaf

#endif // CPAF_DEFS_H
