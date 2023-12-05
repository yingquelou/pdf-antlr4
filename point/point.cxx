#include "point.h"
/* C++ */
Point::Point(const Point &p) : Point(p.x, p.y)
{
}
Point::Point(long x, long y)
{
    this->x = x;
    this->y = y;
}
Point::Point() : Point(0, 0) {}

Point &Point::operator+=(const Point &p)
{
    this->x += p.x;
    this->y += p.y;
    return *this;
}

Point Point::operator+(const Point &p)
{
    return Point(p) += *this;
}

/* C */
#include <stdio.h>
struct point point_Init(long x, long y)
{
    return Point(x, y);
}

struct point point_Add(const struct point *p1, const struct point *p2)
{
    return Point(p1->x + p2->x, p2->y + p1->y);
}

void point_Print(const struct point *p)
{
    printf("(%ld,%ld)", p->x, p->y);
}
