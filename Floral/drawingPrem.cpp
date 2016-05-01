#include "drawingPrem.h"
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include <vector>
#include <algorithm>



void drawPoint(int x, int y){
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f); 

    glVertex2f(px2x(x-2.5f), px2y(y-2.5f));
    // printf("the coordinate is %f %f\n", px2x(x), px2y(y));
    glVertex2f(px2x(x+2.5f), px2y(y-2.5f));
    // printf("the coordinate is %f %f\n", px2x(x+1), px2y(y));
    glVertex2f(px2x(x+2.5f), px2y(y+2.5f));
    // printf("the coordinate is %f %f\n", px2x(x+1), px2y(y+1));
    glVertex2f(px2x(x-2.5f), px2y(y+2.5f));
    // printf("the coordinate is %f %f\n", px2x(x), px2y(y+1));
    glEnd();
}
