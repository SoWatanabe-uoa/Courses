#ifndef POLYGON_H
#define ROLYGON_H

#include <string>
#include <iostream>
#include "shape.h"
#include "point.h"

class Polygon : public Shape {
    public:
    Polygon();
    Polygon(Point*, int);
    Polygon(const Polygon&);
    //Inherited methods
    std::string get_name() const override;
    float compute_area() const override;
    Polygon* create() const override;
    Polygon* clone() const override;
    ~Polygon() override;

    private:
    Point* _vertices;
    int _num_vertices;
};

#endif