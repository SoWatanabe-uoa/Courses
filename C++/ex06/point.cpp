#include "point.h"

Point::Point(float x, float y): _x(x),_y(y) {}

float Point::get_x() const{
    return _x;
}

float Point::get_y() const{
    return _y;
}

void Point::set_x(float x){
    _x = x;
}

void Point::set_y(float y){
    _y = y;
}