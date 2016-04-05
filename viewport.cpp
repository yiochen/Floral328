#include "viewport.h"
#include "constants.h"

GLfloat getWinRawHeight(){
    return glutGet(GLUT_WINDOW_HEIGHT);
}
GLfloat getWinRawWidth(){
    return glutGet(GLUT_WINDOW_WIDTH);
}

GLfloat getWinHeight(){
    return getWinRawHeight()/PIXEL_SIZE;
}
GLfloat getWinWidth(){
    return getWinRawWidth()/PIXEL_SIZE;
}
GLfloat rawx2px(GLfloat raw){
    return raw/PIXEL_SIZE;
}
GLfloat rawy2px(GLfloat raw){
    return getWinHeight()-raw/PIXEL_SIZE-1;
}
/** convert the horizontal length in pixel to length in opengl coordinate**/
GLfloat l2x(GLfloat x){
    return static_cast<GLfloat>(2*x)/static_cast<GLfloat>(getWinWidth());
}
/** convert the vertical length in pixel to length in opengl coordinate**/
GLfloat l2y(GLfloat y){
    return static_cast<GLfloat>(2*y)/static_cast<GLfloat>(getWinHeight());
}

/** convert x in pixel to opengl coordinate**/
GLfloat px2x(GLfloat x){
    return l2x(x)-1;
}

/** convert y in pixel to opengl coordinate**/
GLfloat px2y(GLfloat y){
    return l2y(y)-1;
}
