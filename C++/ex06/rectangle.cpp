#include "Rectangle.h"

Rectangle::Rectangle(): _left_corner(Point()), _width(0.f), _height(0.f){}

Rectangle::Rectangle(Point l_corn, float w, float h): _left_corner(l_corn), _width(w), _height(h) {}

Rectangle::Rectangle(const Rectangle& anotherRec):
_left_corner(anotherRec._left_corner), _width(anotherRec._width), _height(anotherRec._height) {}

std::string Rectangle::get_name() const{
    return "rectangle";
}

float Rectangle::compute_area() const{
    return _width * _height;
}

Rectangle* Rectangle::create() const{
    return new Rectangle();
}

Rectangle* Rectangle::clone() const {
    return new Rectangle(*this);
}

Rectangle::~Rectangle() {
    std::cout << "Rectangle instance deleted" << std::endl;
}
