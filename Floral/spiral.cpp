#include "spiral.h"

#include <cmath>


#include "common.h"
#include "LTexture.h"

extern LTexture* texture;
extern bool useTexture;
void Spiral::draw(bool isSolid, float initWidth, float endWidth){
    printf("drawing spirals\n");
	
    GLfloat rr=this->r;
	if (!isSolid) {
		length = 0;
		glLineWidth(lineWidth);
		glBegin(GL_LINE_STRIP);
		glColor3f(1, 0, 0);
	}
	else {
		if (useTexture) {
			texture->mapStart();
			
		}
		else {
			glBegin(GL_QUAD_STRIP);
			glColor3f(1, 0, 0);
		}
		
	}
    
    
    GLfloat deg=startAngle;
    GLfloat delta;
    if (clockwise){
        delta=-1.0f;
    }else{
        delta=1.0f;
    }
	Vec lastPoint;
	float currentLength = 0;
    while (rr>0){
		GLfloat raddeg = Vec::deg2rad(deg);
        

		if (rr == this->r) lastPoint = Vec(cos(raddeg)*r + x, sin(raddeg)*r + y);
		//flog("deg is %f lastPoint is at %f,%f, and this point is %f, %f", deg, lastPoint.x, lastPoint.y, cos(raddeg)*rr + x, sin(raddeg)*rr + y);
		//flog("length %f add %f", length, Vec::getDistance(cos(raddeg)*rr + x, sin(raddeg)*rr + y, lastPoint.x, lastPoint.y));
		if (!isSolid) {
			length += Vec::getDistance(cos(raddeg)*rr + x, sin(raddeg)*rr + y, lastPoint.x, lastPoint.y);
			glVertex2f(px2x(cos(raddeg)*rr + x), px2y(sin(raddeg)*rr + y));
		}
		else {
			currentLength+= Vec::getDistance(cos(raddeg)*rr + x, sin(raddeg)*rr + y, lastPoint.x, lastPoint.y);
			Vec point(cos(raddeg)*rr + x, sin(raddeg)*rr + y);
			Vec halfWidth(point.x, point.y);
			halfWidth = halfWidth.sub(Vec(x, y)).norm().mul(Vec::lerp(initWidth, endWidth, currentLength, length) / 2);
			//flog("initWidth is %f, halfwidth is %f, %f", initWidth, halfWidth.x, halfWidth.y);
			Vec right(point);
			right = right.sub(halfWidth);
			//flog("right is %f, %f", px2x(right.x), px2y(right.y));
			Vec left(point);
			left = left.add(halfWidth);
			if (useTexture) {
				if (this->clockwise) {
					texture->mapPair(Vec(right.x, right.y), Vec(left.x, left.y), currentLength / length);
				}
				else {
					texture->mapPair(Vec(left.x, left.y), Vec(right.x, right.y), currentLength / length);

				}
			}
			else {
				glVertex2f(px2x(right.x), px2y(right.y));
				glVertex2f(px2x(left.x), px2y(left.y));
			}
			
		}
		
		
		lastPoint = Vec(cos(raddeg)*rr + x, sin(raddeg)*rr + y);

        rr-=(gap/360.0f*abs(delta));
        deg+=delta;
    }
	flog("the length of the spiral is %f", length);
	if (isSolid && useTexture) {
		texture->mapEnd();
	}
	else {
		glEnd();
	}
    glFlush();
}

void Spiral::drawSolid(float initWidth, float endWidth) {
	draw(false, 0, 0);
	draw(true, initWidth, endWidth);
}

void Spiral::draw() {
	draw(false, 0, 0);
}