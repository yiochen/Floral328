#include "viewport.h"
#include "constants.h"

float getWinRawHeight(){
    return glutGet(GLUT_WINDOW_HEIGHT);
}
float getWinRawWidth(){
    return glutGet(GLUT_WINDOW_WIDTH);
}

float getWinHeight(){
    return getWinRawHeight()/PIXEL_SIZE;
}
float getWinWidth(){
    return getWinRawWidth()/PIXEL_SIZE;
}
float rawx2px(float raw){
    return raw/PIXEL_SIZE;
}
float rawy2px(float raw){
    return getWinHeight()-raw/PIXEL_SIZE-1;
}
/** convert the horizontal length in pixel to length in opengl coordinate**/
float l2x(float x){
    return static_cast<float>(2*x)/static_cast<float>(getWinWidth());
}
/** convert the vertical length in pixel to length in opengl coordinate**/
float l2y(float y){
    return static_cast<float>(2*y)/static_cast<float>(getWinHeight());
}

/** convert x in pixel to opengl coordinate**/
float px2x(float x){
    return l2x(x)-1;
}

/** convert y in pixel to opengl coordinate**/
float px2y(float y){
    return l2y(y)-1;
}
