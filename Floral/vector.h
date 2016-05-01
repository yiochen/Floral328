#ifndef VECTOR_H
#define VECTOR_H

#include "opengl_include.h"
#include <math.h>

class Vec{

public:
    GLfloat x, y;
    Vec();
    Vec(GLfloat x, GLfloat y);
    Vec add(Vec v2);
	Vec sub(Vec v2);
    Vec neg();
    Vec norm();
    Vec mul(GLfloat s);
    GLfloat mag();
	/*the angle of the vector is calculated in degree. 
	it starts from the x positive (0 degree), increases clockwise and returns back to x positive at 360 deg. 
	So y positive is 90 deg. x negative is 180 deg.
	*/
    GLfloat angle();
	static float PI;
	static float regulizeDeg(float deg) {
		while (deg >= 360.0f) deg -= 360.0f;
		while (deg < 0) deg += 360.0f;
		return deg;
	}
	static float deg2rad(float deg) { return regulizeDeg(deg) / PI; }
	static float rad2deg(float rad) { return regulizeDeg(rad*PI); }
};

#endif
