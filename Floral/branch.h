//branch contains at most two stems and one leaf.
#ifndef BRANCH_H
#define BRANCH_H

#include "opengl_include.h"
#include "shape.h"
#include "circle.h"
#include <list>
using namespace std;
class Branch : public Shape{
public:
    Branch(GLfloat x, GLfloat y, Vec root):Shape(x, y){this->root=root;}
    Branch():Branch(50.0f,0.0f,Vec(0.0f,1.0f)){}
    Vec root;
    list<Circle*> parts;
    Branch* add(Circle* part);
    void draw() override;
};

#endif
