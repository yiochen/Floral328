#include "viewport.h"
#include "constants.h"

GLfloat getWinRawHeight(){
    return glutGet(GLUT_WINDOW_HEIGHT);
}
GLfloat getWinRawWidth(){
    return glutGet(GLUT_WINDOW_WIDTH);
}

GLfloat getWinHeight(){
    return getWinRawHeight();
}
GLfloat getWinWidth(){
    return getWinRawWidth();
}
GLfloat rawx2px(GLfloat raw){
    return raw;
}
GLfloat rawy2px(GLfloat raw){
    return getWinHeight()-raw;
}
/** convert the horizontal length in pixel to length in opengl coordinate**/
GLfloat l2x(GLfloat x){
    return x;
}
/** convert the vertical length in pixel to length in opengl coordinate**/
GLfloat l2y(GLfloat y){
    return y;
}

/** convert x in pixel to opengl coordinate**/
GLfloat px2x(GLfloat x){
    return x;
}

/** convert y in pixel to opengl coordinate**/
GLfloat px2y(GLfloat y){
    return getWinHeight()-y;
}
