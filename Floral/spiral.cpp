#include "spiral.h"

#include <cmath>


#include "common.h"

void Spiral::draw(){
    printf("drawing spirals\n");
	length = 0;
    GLfloat rr=this->r;
    glLineWidth(lineWidth);
    glBegin(GL_LINE_STRIP);
    glColor3f(1,0,0);
    GLfloat deg=startAngle;
    GLfloat delta;
    if (clockwise){
        delta=-1.0f;
    }else{
        delta=1.0f;
    }
	Vec lastPoint;
    while (rr>0){
		GLfloat raddeg = Vec::deg2rad(deg);
        glVertex2f(px2x(cos(raddeg)*rr+x),px2y(sin(raddeg)*rr+y));

		if (rr == this->r) lastPoint = Vec(cos(raddeg)*r + x, sin(raddeg)*r + y);
		//flog("deg is %f lastPoint is at %f,%f, and this point is %f, %f", deg, lastPoint.x, lastPoint.y, cos(raddeg)*rr + x, sin(raddeg)*rr + y);
		//flog("length %f add %f", length, Vec::getDistance(cos(raddeg)*rr + x, sin(raddeg)*rr + y, lastPoint.x, lastPoint.y));
		length += Vec::getDistance(cos(raddeg)*rr + x, sin(raddeg)*rr + y, lastPoint.x, lastPoint.y);
		
		lastPoint = Vec(cos(raddeg)*rr + x, sin(raddeg)*rr + y);

        rr-=(gap/360.0f*abs(delta));
        deg+=delta;
    }
	flog("the length of the spiral is %f", length);
    glEnd();
    glFlush();
}
