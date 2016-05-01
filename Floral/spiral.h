#ifndef SPIRAL_H
#define SPIRAL_H
#include "circle.h"

class Spiral:public Circle{
public:
	Spiral(GLfloat x, GLfloat y, GLfloat r, GLfloat startAngle) :Circle(x, y, r) { this->startAngle = startAngle; this->gap = 100.0f; this->clockwise = true; length = 0; }
    Spiral():Spiral(0.0f,0.0f,50.0f,0.0f){}
    void draw() override;
	void draw(bool isSolid, float initWidth, float endWidth);
	void drawSolid(float initWidth, float endWidth) override;
    GLfloat gap;
};

#endif
