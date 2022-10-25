#ifndef DISK_H
#define DISK_H

#include <string>
#include <iostream>
#include <cmath>
#include "shape.h"
#include "point.h"

class Disk : public Shape {
    public:
    Disk();
    Disk(Point, float);
    Disk(const Disk&);
    //Inherited methods
    std::string get_name() const override;
    float compute_area() const override;
    Disk* create() const override;
    Disk* clone() const override;
    ~Disk() override;

    private:
    Point _center;
    float _radius;
};

#endif