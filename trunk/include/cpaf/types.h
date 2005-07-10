/*!
    \file include/cpaf/types.h
    \brief Basic cpaf types
    \date Crated: 2005-04-05
*/

#ifndef CPAF_TYPES_H
#define CPAF_TYPES_H

#include <stddef.h>
#include <cpaf/dllimpexp.h>

namespace cpaf {

//! \todo decide wether we use addresses or object id's here
typedef int object_id; // value specifying which object sent the event

/*!
    \brief Data structure representing a size using floating point values.
*/
struct CPAF_API Size
{
    float width, height;

    /*!
        Default constructor, initializes values to 0
    */
    Size()
        : width(0),
        height(0)
    { }

    /*!
        Constructs a Size object from a width and height.
        \param w Width
        \param h Height
    */
    Size(float w, float h)
        : width(w),
        height(h)
    { }

    /*!
        Adds the width and height from size \a s to this size's width and height.
    */
    Size &operator+=(const Size &s)
    {
        width += s.width;
        height += s.height;
        return *this;
    }

    /*!
        Subtracts the width and height from size \a s from this size's width and height.
    */
    Size &operator-=(const Size &s)
    {
        width -= s.width;
        height -= s.height;
        return *this;
    }

    /*!
        Multiply the height and width of this size by the factor \a f.
    */
    Size &operator*=(float f)
    {
        width *= f;
        height *= f;
        return *this;
    }

    /*!
        Divide the height and width of this size by the factor \a f.
    */
    Size &operator/=(float f)
    {
        width /= f;
        height /= f;
        return *this;
    }

    /*!
        \return True if this size is equal to the size \a s.
    */
    bool operator==(const Size &s)
    {
        return width == s.width && height == s.height;
    }

    /*!
        \return True if this size is not equal to the size \a s.
    */
    bool operator!=(const Size &s)
    {
        return width != s.width || height != s.height;
    }

    friend Size CPAF_API operator+(const Size &l, const Size &r);
    friend Size CPAF_API operator-(const Size &l, const Size &r);
    friend Size CPAF_API operator*(const Size &l, float f);
    friend Size CPAF_API operator/(const Size &l, float f);
};

/*!
    \brief Class representing a point using floating point values.
*/
struct CPAF_API Point
{
    float x, y;

    /*!
        Default constructor, initializes values to 0
    */
    Point()
        : x(0),
        y(0)
    { }

    /*!
        Constructs a Point from an x and y value.
        \param xx X value
        \param yy Y value
    */
    Point(float xx, float yy)
        : x(xx),
        y(yy)
    { }

    /*!
        Add the x and y values of position \a p to this position's x and y values.
    */
    Point &operator+=(const Point &p)
    {
        x += p.x;
        y += p.y;
        return *this;
    }

    /*!
        Subtract the x and y values of position \a p from this position's x and y values.
    */
    Point &operator-=(const Point &p)
    {
        x -= p.x;
        y -= p.y;
        return *this;
    }

    /*!
        \return True if this position is equal to the position \a p.
    */
    bool operator==(const Point &p)
    {
        return x == p.x && y == p.y;
    }

    /*!
        \return True if this position is not equal to the position \a p.
    */
    bool operator!=(const Point &p)
    {
        return x != p.x || y != p.y;
    }
};

/*!
    \brief Data structure representing a rectangle, which is composed of an origin position and a size
*/
struct CPAF_API Rect
{
    Size size;
    Point position;

    /*!
        Default constructor, initializes size and position to 0
    */
    Rect()
        : size(0,0),
        position(0,0)
    { }

    /*!
        Constructs a Rect from a position and a size
        \param p Position
        \param s Size
    */
    Rect(const Point &p, const Size &s)
        : size(s),
        position(p)
    { }

    /*!
        Constructs a Rect from a position and size defined as four floating point values.
        \param x X position
        \param y Y position
        \param w Width
        \param h Height
    */
    Rect(float x, float y, float w, float h)
        : size(w,h),
        position(x,y)
    { }

    /*!
        \return True if this rect is equal to the rect \a r.
    */
    bool operator==(const Rect &r)
    {
        return size == r.size && position == r.position;
    }

    /*!
        \return True if this rect is not equal to the rect \a r.
    */
    bool operator!=(const Rect &r)
    {
        return size != r.size || position != r.position;
    }

    friend Point CPAF_API operator+(const Point &l, const Point &r);
    friend Point CPAF_API operator-(const Point &l, const Point &r);
};

// default position and size constants
/*
const float DEFAULT_VALUE(-1);
const Point DEFAULT_POS(DEFAULT_VALUE, DEFAULT_VALUE);
const Size DEFAULT_SIZE(DEFAULT_VALUE, DEFAULT_VALUE);
*/

} // namespace cpaf

#endif // CPAF_DEFS_H
