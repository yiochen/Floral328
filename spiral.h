#ifndef SPIRAL_H
#define SPIRAL_H
#include "circle.h"

class Spiral:public Circle{
public:
    Spiral(GLfloat x, GLfloat y, GLfloat r, GLfloat startAngle):Circle(x, y, r){this->startingAngle=startAngle;}
    void draw() override;

}

#endif
