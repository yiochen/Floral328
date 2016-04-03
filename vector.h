#ifndef VECTOR_H
#define VECTOR_H

#include "opengl_include.h"


class Vec{
    GLfloat x, y;
public:
    Vec();
    Vec(GLfloat x, GLfloat y);
    Vec add(Vec v2);
    Vec neg();
    Vec norm();
    Vec mul(GLfloat s);
    GLfloat mag();
};

#endif
