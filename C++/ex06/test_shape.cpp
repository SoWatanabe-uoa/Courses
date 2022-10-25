// COMPLETE include the necessary headers
#include <iostream>
#include <string>
#include <cmath>
#include "shape.h"
#include "rectangle.h"
#include "disk.h"
#include "Polygon.h"
#include "point.h"
#include "utils.h"

int main(void) {
  //Test for Q2
  float width=2.f, height=4.f, radius=1.f;
  Point l_corn(1.f,2.f), center(-5.f,-5.f);

  std::cout << "------Q2------" << std::endl;
  std::cout << "Test for Rectangle class" << std::endl;
  Rectangle rectangle(l_corn,width,height);
  Rectangle* createdRectangle = rectangle.create();
  Rectangle* clonedRectangle = rectangle.clone();
  std::cout << "Name: " << rectangle.get_name() << ", Area: " << rectangle.compute_area() << std::endl;
  std::cout << "Name: " << createdRectangle->get_name() << ", Area: " << createdRectangle->compute_area() << std::endl;
  std::cout << "Name: " << clonedRectangle->get_name() << ", Area: " << clonedRectangle->compute_area() << std::endl;
  delete createdRectangle;
  delete clonedRectangle;

  std::cout << "Test for Disk class" << std::endl;
  Disk disk(center,radius);
  Disk* createdDisk = disk.create();
  Disk* clonedDisk = disk.clone();
  std::cout << "Name: " << disk.get_name() << ", Area: " << disk.compute_area() << std::endl;
  std::cout << "Name: " << createdDisk->get_name() << ", Area: " << createdDisk->compute_area() << std::endl;
  std::cout << "Name: " << clonedDisk->get_name() << ", Area: " << clonedDisk->compute_area() << std::endl;
  delete createdDisk;
  delete clonedDisk;


  //Test for Q3
  Point vertices_test1[4] = {Point(1.f,1.f),Point(1.f,-1.f),Point(-1.f,-1.f),Point(-1.f,1.f)};
  Point vertices_test2[64];
  for(int i=0; i<64; i++){
    vertices_test2[i].set_x( (float)cos( ((2.0*M_PI)/64.0)*double(i) ) );
    vertices_test2[i].set_y( (float)sin( ((2.0*M_PI)/64.0)*double(i) ) );
  }

  std::cout << "\n------Q3------" << std::endl;
  std::cout << "Test1" << std::endl;
  Polygon polygon1(vertices_test1,4);
  Polygon* createdPolygon1 = polygon1.create();
  Polygon* clonedPolygon1 = polygon1.clone();
  std::cout << "Name: " << polygon1.get_name() << ", Area: " << polygon1.compute_area() << std::endl;
  std::cout << "Name: " << createdPolygon1->get_name() << ", Area: " << createdPolygon1->compute_area() << std::endl;
  std::cout << "Name: " << clonedPolygon1->get_name() << ", Area: " << clonedPolygon1->compute_area() << std::endl;
  delete createdPolygon1;
  delete clonedPolygon1;

  std::cout << "Test2" << std::endl;
  Polygon polygon2(vertices_test2,64);
  Polygon* createdPolygon2 = polygon2.create();
  Polygon* clonedPolygon2 = polygon2.clone();
  std::cout << "Name: " << polygon2.get_name() << ", Area: " << polygon2.compute_area() << std::endl;
  std::cout << "Name: " << createdPolygon2->get_name() << ", Area: " << createdPolygon2->compute_area() << std::endl;
  std::cout << "Name: " << clonedPolygon2->get_name() << ", Area: " << clonedPolygon2->compute_area() << std::endl;
  delete createdPolygon2;
  delete clonedPolygon2;

   return 0;
}