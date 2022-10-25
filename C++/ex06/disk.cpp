#include "Disk.h"

Disk::Disk(): _center(Point()), _radius(0.f) {}

Disk::Disk(Point center, float radius): _center(center), _radius(radius) {}

Disk::Disk(const Disk& anotherDisk):
_center(anotherDisk._center), _radius(anotherDisk._radius) {}

std::string Disk::get_name() const{
    return "Disk";
}

float Disk::compute_area() const{
    return (float)M_PI * _radius * _radius;
}

Disk* Disk::create() const{
    return new Disk();
}

Disk* Disk::clone() const {
    return new Disk(*this);
}

Disk::~Disk() {
    std::cout << "Disk instance deleted" << std::endl;
}
