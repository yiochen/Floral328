#include "common.h"
#include "circle.h"
#include "canvas.h"


#include <math.h>
#include <stdio.h>

#include "LTexture.h"

extern LTexture* texture;
extern bool useTexture;

bool Circle::endCondition(GLfloat i) {
	if (clockwise) return i > startAngle - range;
	else return i < startAngle + range;
}
void Circle::draw(bool isSolid, float initWidth, float endWidth){
	//glLineWidth(lineWidth);
	glLineWidth(0);
	if (!isSolid) {
		this->length = 0.0f;
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
    
    
	GLfloat delta;
	if (clockwise) {
		delta = -1.0f;
	}
	else {
		delta = 1.0f;
	}
    
	Vec lastPoint;
	float currentLength = 0;
    for (GLfloat i=startAngle; endCondition(i);i+=delta){
        float deg=Vec::deg2rad(i);
		if (i == startAngle) lastPoint = Vec(cos(deg)*r + x, sin(deg)*r + y);
		if (!isSolid) {
			glVertex2f(px2x(cos(deg)*r + x), px2y(sin(deg)*r + y));
			//calculating length
			length += Vec::getDistance(cos(deg)*r + x, sin(deg)*r + y, lastPoint.x, lastPoint.y);
				
		}else {
			currentLength += Vec::getDistance(cos(deg)*r + x, sin(deg)*r + y, lastPoint.x, lastPoint.y);
			Vec point(cos(deg)*r + x, sin(deg)*r + y);
			Vec halfWidth(point.x, point.y);
			halfWidth = halfWidth.sub(Vec(x, y)).norm().mul(Vec::lerp(initWidth,endWidth,currentLength,length)/2);
			//flog("initWidth is %f, halfwidth is %f, %f", initWidth, halfWidth.x, halfWidth.y);
			Vec right(point);
			right=right.sub(halfWidth);
			//flog("right is %f, %f", px2x(right.x), px2y(right.y));
			Vec left(point);
			left=left.add(halfWidth);
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
		lastPoint = Vec(cos(deg)*r + x, sin(deg)*r + y);
    }
  
	//flog("the length of the circle is is %f", length);
	if (isSolid && useTexture) {
		texture->mapEnd();
	}
	else {
		glEnd();
	}
    
    glFlush();
}
void Circle::draw() {
	draw(false,0,0);
}
void Circle::drawSolid(float initWidth, float endWidth) {
	draw(false, initWidth, endWidth);//draw first to calculate the length
	draw(true,initWidth, endWidth);
}
bool Circle::pointAt(Vec v){
    Vec center(this->x, this->y);
    Vec dis=v.add(center.neg());
    printf("the dis is %f\n",dis.mag());
    if (abs(dis.mag()-this->r)<=EPSILON){
        //the difference is close enough, so can conclude that the point is on the circle.
        //check if it is within the angular span
        GLfloat ang=dis.angle();
        GLfloat start;
        GLfloat end;
        if (clockwise){
            start=this->startAngle-this->range;
            end=this->startAngle;
            if (start<0){
                start+=360.0f;
                end+=360.0f;
            }
        }else{
            start=this->startAngle;
            end=this->startAngle+this->range;
        }


        printf("the angle is at %f\n", ang);
        if (ang>=start&& ang<=end){
            return true;
        }
    }
    return false;
}

bool Circle::touching(Circle* circle){
    Vec v1(circle->x, circle->y);
    Vec v2(this->x, this->y);
    Vec dis=v1.add(v2.neg());
    if (dis.mag()<=circle->r+this->r+EPSILON) return true;
    else return false;
}
//this function will find the point in between the center of the two circle
// which is also the center of the two intersecting points
Vec Circle::touchingAt(Circle* circle){
    if (!(this->touching(circle))) return Vec(0.0f,0.0f);
    Vec v1(circle->x, circle->y);
    Vec v2(this->x, this->y);
    Vec dis=v1.add(v2.neg());
    GLfloat ratio;
    if (this->inside(circle)){
        ratio=this->r/(this->r-circle->r);
    }else{
        ratio=this->r/(this->r+circle->r);
    }
    Vec v3=v2.add(dis.norm().mul(ratio*dis.mag()));
   // printf("touching at %f, %f\n", v3.x, v3.y);
    return v3;
}

bool Circle::inside(Circle* circle){
    Vec dis(circle->x-this->x, circle->y-this->y);
    return dis.mag()<this->r;
}

bool Circle::inside(Vec v){
    Vec dis(this->x-v.x, this->y-v.y);
    return dis.mag()<this->r;
}

