#include "circle.h"
#include <cmath>
using namespace std;

double distance(const Circle *c, const Point *p) {
  return (pow(p->x - c->centre.x, 2) + pow(p->y - c->centre.y, 2)) /
         pow(c->radius, 2);
}

string CheckPointInCircle(double distance) {
  if (distance > 1 + EPSILON) {
    return "Outside";
  } else if (distance < 1 - EPSILON) {
    return "Inside";
  } else {
    return "On Circle";
  }
}
