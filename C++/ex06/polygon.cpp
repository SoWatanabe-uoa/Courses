#include "Polygon.h"

Polygon::Polygon(const Point2D* v, int n): P(new Point2D[n]),N(n) {
    for(int i=0; i < n; i++) P[i] = v[i];
}

Polygon::~Polygon(){
    delete[] P;
}

std::string Polygon::get_name() const {
    return "polygon";
}

float Polygon::compute_area() const {
    float area = 0.0f;
    int next=-1;
    for(int i=0; i <= N-1; i++){
        if(next == N-1) next = 0;
        else next = i+1;
        area += P[i].get_x() * P[next].get_y() - P[i].get_y() * P[next].get_x();
    }
    return area / 2.0f;
}

void Polygon::translate(float tx, float ty) {
    for(int i=0; i < N; i++){
        P[i].set_x(P[i].get_x() + tx);
        P[i].set_y(P[i].get_y() + ty);
    }
}