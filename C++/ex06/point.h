#ifndef POINT_H
#define POINT_H

class Point{
    public:
    Point(float x=0.f,float y=0.f);

    float get_x() const;
    float get_y() const;
    void set_x(float);
    void set_y(float);
    
    private:
    float _x;
    float _y;
};

#endif