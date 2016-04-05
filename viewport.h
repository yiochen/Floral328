#ifndef H_VIEWPORT
#define H_VIEWPORT
/** The viewport has a coordinate system that
*   origins from the left bottom corner of the window.
*   X-axis points right, Y-asix points up.
*   The smallest unit in the system is PIXEL_SIZE width and height
**/
#include "opengl_include.h"


GLfloat getWinHeight();
GLfloat getWinWidth();

GLfloat rawx2px(GLfloat raw);
GLfloat rawy2px(GLfloat raw);
/** convert the horizontal length in pixel to length in opengl coordinate**/
GLfloat l2x(GLfloat x);
/** convert the vertical length in pixel to length in opengl coordinate**/
GLfloat l2y(GLfloat y);
/** convert x in pixel to opengl coordinate**/
GLfloat px2x(GLfloat x);
/** convert y in pixel to opengl coordinate**/
GLfloat px2y(GLfloat y);

#endif
