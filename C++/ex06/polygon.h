#ifndef POLYGON_H
#define POLYGON_H

#include <string>
#include "Shape2D.h"
#include "Point2D.h"

class Polygon : public Shape2D {
    public:
    Polygon(const Point2D*, int);
    ~Polygon();

    std::string get_name() const override;

    float compute_area() const override;

    void translate(float tx, float ty) override;

    private:
    Point2D* P;
    int N;
};

#endif