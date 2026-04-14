#ifndef CIRCLE_H
#define CIRCLE_H

#include "point.h"
#include <string>

struct Circle {
    Point centre;
    double radius;
};

inline constexpr double EPSILON = 1e-9;

double distance(const Circle * c,const Point * p);


std::string CheckPointInCircle(double distance);

#endif