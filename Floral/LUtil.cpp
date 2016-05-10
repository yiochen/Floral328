
#include "LUtil.h"
#include "LTexture.h"
#include "common.h"
#include "vector.h"
#include <chrono>
#include <thread>
#include <vector>
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

void angleTest() {
	Vec a(0, 1);
	Vec b(1, 1);
	Vec c(-1, 1);
	Vec d(-1, 0);
	Vec e(-1, -1);
	Vec f(1, -1);
	printf("the angle of 0,1 is %f\n", a.angle());
	printf("the angle of 1,1 is %f\n", b.angle());
	printf("the angle of -1,1 is %f\n", c.angle());
	printf("the angle of -1,0 is %f\n", d.angle());
	printf("the angle of -1,-1 is %f\n", e.angle());
	printf("the angle of 1,-1 is %f\n", f.angle());
}
void screenshot() {
	int w = getWinWidth();
	int h = getWinHeight();
	std::vector< unsigned char > buf(w * h * 3);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, &buf[0]);
	int save_result = SOIL_save_image(
		"new_screenshot.bmp",
		SOIL_SAVE_TYPE_BMP ,
		w, h, 3,
		&buf[0]
		);
	if (save_result == 1) {
		printf("successfully saved screenshot\n");
	}
	else {
		printf("saving screenshot failed\n");
	}
}

void pause() {
	std::this_thread::sleep_for(std::chrono::milliseconds(20));
}