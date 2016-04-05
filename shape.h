//abstract class for shapes
#ifndef SHAPE_H
#define SHAPE_H
#include "opengl_include.h"
class Shape{

public:
    Shape(GLfloat x, GLfloat y){this->x=x; this->y=y;lineWidth=1.5;}
    Shape():Shape(0.0f,0.0f){}
    GLfloat lineWidth;
    GLfloat x;
    GLfloat y;
    virtual void draw()=0;
};

#endif
