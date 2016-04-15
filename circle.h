#ifndef CIRCLE_H
#define CIRCLE_H

#include "opengl_include.h"
#include "shape.h"
#include "vector.h"

class Circle : public Shape{
public:
    Circle(GLfloat x, GLfloat y, GLfloat r):Shape(x, y){this->r=r; this->startAngle=0;this->range=360; this->clockwise=true;}
    Circle():Circle(0.0f,0.0f,10.0f){}
    Circle(GLfloat x, GLfloat y):Circle(x, y,10.0f){}
    Circle(GLfloat r):Circle(0.0f,0.0f,r){}
    GLfloat startAngle;
    GLfloat range;
    GLfloat r;
    bool clockwise;
    virtual void draw() override;
    //check if a point is on the arc
    bool pointAt(Vec v);
    bool touching(Circle* circle);
    Vec touchingAt(Circle* circle);
    bool inside(Circle* v);
    bool inside(Vec v);
};

#endif
