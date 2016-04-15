#ifndef STEM_H
#define STEM_H

#include "circle.h"
class Stem : public Circle{
public:
    Stem(GLfloat x, GLfloat y, GLfloat r, GLfloat startAngle):Circle(x,y,r){ this.startAngle=startAngle}
}
#endif
