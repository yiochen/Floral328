
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
