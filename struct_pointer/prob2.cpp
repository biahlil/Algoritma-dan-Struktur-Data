#include "circle.h"
#include <iostream>
using namespace std;

int main() {
    Circle circle1;
    Point point1;

    cin >> circle1.centre.x >> circle1.centre.y >> circle1.radius;
    cin >> point1.x >> point1.y;

    cout << CheckPointInCircle(distance(&circle1, &point1));

    return 0;
}