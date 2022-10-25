#include "polygon.h"

Polygon::Polygon(): _vertices(nullptr), _num_vertices(0) {}

Polygon::Polygon(Point* vertices, int num_vertices): _vertices(new Point[num_vertices]), _num_vertices(num_vertices) {
    for(int i=0; i<num_vertices; i++) _vertices[i] = vertices[i];
}

Polygon::Polygon(const Polygon& anotherPoly):
 _vertices(new Point[anotherPoly._num_vertices]), _num_vertices(anotherPoly._num_vertices) {
    for(int i=0; i<anotherPoly._num_vertices; i++) _vertices[i] = anotherPoly._vertices[i];
 }

std::string Polygon::get_name() const{
    return "polygon";
}

float Polygon::compute_area() const{
    float area=0.f;
    for(int i=0; i<_num_vertices; i++){
        area += _vertices[i].get_x() * _vertices[(i+1)%_num_vertices].get_y() -
        _vertices[i].get_y() * _vertices[(i+1)%_num_vertices].get_x();
    }
    return area / 2.f;
}

Polygon* Polygon::create() const{
    return new Polygon();
}

Polygon* Polygon::clone() const {
    return new Polygon(*this);
}

Polygon::~Polygon() {
    delete[] _vertices;
    std::cout << "Polygon instance deleted" << std::endl;
}
