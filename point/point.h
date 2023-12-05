#pragma once
#ifdef __cplusplus
extern "C"
{
#endif
    struct point
    {
        long x;
        long y;
    };
#ifdef __cplusplus
}

#endif

#ifdef __cplusplus

class Point : public point
{
private:
    /* data */
public:
    // Point(/* args */);
    // ~Point();

    Point(const Point &);
    Point(long x, long y);
    Point();
    Point &operator+=(const Point &);
    Point operator+(const Point &);
};
#else
typedef struct point Point;
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    struct point point_Init(long x, long y);
    struct point point_Add(const struct point *p1, const struct point *p2);
    void point_Print(const struct point *);
#ifdef __cplusplus
}
#endif