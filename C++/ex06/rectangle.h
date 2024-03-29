#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>
#include <iostream>
#include "shape.h"
#include "point.h"

class Rectangle : public Shape {
    public:
    Rectangle();
    Rectangle(Point, float, float);
    Rectangle(const Rectangle&);
    //Inherited methods
    std::string get_name() const override;
    float compute_area() const override;
    Rectangle* create() const override;
    Rectangle* clone() const override;
    ~Rectangle() override;

    private:
    Point _left_corner;
    float _width;
    float _height;
};

#endif