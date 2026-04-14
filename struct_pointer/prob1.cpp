#include "line.h"
#include <iostream>
using namespace std;

int main() {
    Line line1;
    Point point1;
    
    cin >> line1.a >> line1.b >> line1.c;
    cin >> point1.x >> point1.y;

    cout << CheckPointPosition(gradient(&line1, &point1));

    return 0;
} 