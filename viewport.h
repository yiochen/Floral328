#ifndef H_VIEWPORT
#define H_VIEWPORT
/** The viewport has a coordinate system that
*   origins from the left bottom corner of the window.
*   X-axis points right, Y-asix points up.
*   The smallest unit in the system is PIXEL_SIZE width and height
**/
#include "opengl_include.h"


float getWinHeight();
float getWinWidth();

float rawx2px(float raw);
float rawy2px(float raw);
/** convert the horizontal length in pixel to length in opengl coordinate**/
float l2x(float x);
/** convert the vertical length in pixel to length in opengl coordinate**/
float l2y(float y);
/** convert x in pixel to opengl coordinate**/
float px2x(float x);
/** convert y in pixel to opengl coordinate**/
float px2y(float y);

#endif
