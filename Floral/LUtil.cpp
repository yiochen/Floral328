
#include "LUtil.h"
#include "LTexture.h"
#include "common.h"

//Checkerboard texture
LTexture gCheckerBoardTexture;

bool initGL()
{
	//Set the viewport
	glViewport(0.f, 0.f, getWinWidth(), getWinHeight());

	//Initialize Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, getWinWidth(), getWinHeight(), 0.0, 1.0, -1.0);

	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Initialize clear color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//Enable texturing
	glEnable(GL_TEXTURE_2D);

	//Check for error
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		return false;
	}

	return true;
}

void lReshape(int width, int height) {
	printf("the height of the window is %f\n", getWinHeight());
	glViewport(0.f, 0.f, getWinWidth(), getWinHeight());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, getWinWidth(), getWinHeight(), 0.0, 1.0, -1.0);
	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
}
void lDisplay() {

}
