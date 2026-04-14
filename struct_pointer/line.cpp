#include "line.h"
using namespace std;

double gradient(const Line * l,const Point * p){
    return l->a * p->x + l->b * p->y + l->c;
}

string CheckPointPosition(double gradient){
    if(gradient > EPSILON){
        return "Left";
    }else if(gradient < -EPSILON){
        return "Right";
    }else{
        return "On Line";
    }
}