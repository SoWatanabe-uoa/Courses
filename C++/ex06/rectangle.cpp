#include "Rectangle.h"

Rectangle::Rectangle(): _left_corner(Point()), _width(0.f), _height(0.f){}

Rectangle::Rectangle(Point l_corn, float w, float h): _left_corner(l_corn), _width(w), _height(h) {}

Rectangle::Rectangle(const Rectangle& anotherRec):
_left_corner(anotherRec._left_corner), _width(anotherRec._width), _height(anotherRec._height) {}

std::string Rectangle::get_name() const override{
    return "rectangle";
}

float Rectangle::compute_area() const override{
    return _width * _height;
}

Shape* Rectangle::create() const override{
    return new Rectangle();
}

Shape* clone() const override{
    //return new Rectangle(*this);
    Rectangle r(*this);
    return;
}
