#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>
#include "shape.h"
#include "point.h"

class Rectangle : public Shape {
    public:
    Rectangle();
    Rectangle(Point, float, float);
    Rectangle(const Rectangle&);

    std::string get_name() const override;
    float compute_area() const override;
    Shape* create() const override;
    Shape* clone() const override;
    ~Shape2D() override;

    private:
    Point _left_corner;
    float _width;
    float _height;
};

#endif