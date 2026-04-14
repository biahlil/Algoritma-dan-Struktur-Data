#ifndef LINE_H
#define LINE_H

#include "point.h"
#include <string>

struct Line {
    double a;
    double b;
    double c;
}; 

inline constexpr double EPSILON = 1e-9;

double gradient(const Line * l,const Point * p);

std::string CheckPointPosition(double gradient);

#endif