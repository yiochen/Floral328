
#include "circle.h"
#include "canvas.h"
#include "constants.h"
#include "viewport.h"
#include <math.h>
#include <stdio.h>


void Circle::draw(){
    printf("drawing cirlce");
    glLineWidth(lineWidth);
    glBegin(GL_LINE_STRIP);

    glColor3f(1,0,0);
    for (GLfloat i=startAngle; i<=startAngle+range;i+=1.0f){
        float deg=i*DEG2RAD;
        glVertex2f(px2x(cos(deg)*r+x), px2y(sin(deg)*r+y));
    }
    glEnd();
    glFlush();
}

bool Circle::pointAt(Vec v){
    Vec center(this->x, this->y);
    Vec dis=v.add(center.neg());
    printf("the dis is %f\n",dis.mag());
    if (abs(dis.mag()-this->r)<=EPSILON){
        //the difference is close enough, so can conclude that the point is on the circle.
        //check if it is within the angular span
        GLfloat ang=dis.angle();
        printf("the angle is at %f\n", ang);
        if (ang>this->startAngle && ang<startAngle+range){
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
    printf("dis is %f, %f,\n", dis.x, dis.y);
    GLfloat ratio=this->r/(this->r+circle->r);
    return v2.add(dis.norm().mul(ratio*dis.mag()));
}
