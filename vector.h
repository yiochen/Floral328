#ifndef VECTOR_H
#define VECTOR_H

#include "opengl_include.h"


class Vec{

public:
    GLfloat x, y;
    Vec();
    Vec(GLfloat x, GLfloat y);
    Vec add(Vec v2);
    Vec neg();
    Vec norm();
    Vec mul(GLfloat s);
    GLfloat mag();
};

#endif
