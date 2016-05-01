#ifndef SPIRAL_H
#define SPIRAL_H
#include "circle.h"

class Spiral:public Circle{
public:
    Spiral(GLfloat x, GLfloat y, GLfloat r, GLfloat startAngle):Circle(x, y, r){this->startAngle=startAngle;this->gap=100.0f;this->clockwise=true;}
    Spiral():Spiral(0.0f,0.0f,50.0f,0.0f){}
    void draw() override;
    GLfloat gap;
};

#endif
