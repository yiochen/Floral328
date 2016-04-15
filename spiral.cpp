#include "spiral.h"
#include "constants.h"
#include <math.h>
#include "viewport.h"
#include <stdio.h>

void Spiral::draw(){
    printf("drawing spirals\n");
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

    while (rr>0){
        GLfloat raddeg=deg*DEG2RAD;
        glVertex2f(px2x(cos(raddeg)*rr+x),px2y(sin(raddeg)*rr+y));
        rr-=(gap/360.0f*abs(delta));
        deg+=delta;
    }
    glEnd();
    glFlush();
}
