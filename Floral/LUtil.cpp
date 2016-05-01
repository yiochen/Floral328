
#include "LUtil.h"
#include "LTexture.h"
#include "constants.h"

//Checkerboard texture
LTexture gCheckerBoardTexture;

bool initGL()
{
	//Set the viewport
	glViewport(0.f, 0.f, SCR_W, SCR_H);

	//Initialize Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, SCR_W, SCR_H, 0.0, 1.0, -1.0);

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
//bool lLoadMedia()
//{
//	printf("loading texture\n");
//	//Checkerboard pixels
//	const int CHECKERBOARD_WIDTH = 128;
//	const int CHECKERBOARD_HEIGHT = 128;
//	const int CHECKERBOARD_PIXEL_COUNT = CHECKERBOARD_WIDTH * CHECKERBOARD_HEIGHT;
//	GLuint checkerBoard[CHECKERBOARD_PIXEL_COUNT];
//	//Go through pixels
//	for (int i = 0; i < CHECKERBOARD_PIXEL_COUNT; ++i)
//	{
//		//Get the individual color components
//		GLubyte* colors = (GLubyte*)&checkerBoard[i];
//		//If the 5th bit of the x and y offsets of the pixel do not match
//		if (i / 128 & 16 ^ i % 128 & 16)
//		{
//			//Set pixel to white
//			colors[0] = 0xFF;
//			colors[1] = 0xFF;
//			colors[2] = 0xFF;
//			colors[3] = 0xFF;
//		}
//		else
//		{
//			//Set pixel to red
//			colors[0] = 0xFF;
//			colors[1] = 0x00;
//			colors[2] = 0x00;
//			colors[3] = 0xFF;
//		}
//	}//Load texture
//    if (!gCheckerBoardTexture.loadTextureFromPixels32(checkerBoard, CHECKERBOARD_WIDTH, CHECKERBOARD_HEIGHT))
//	{
//		printf("Unable to load checkerboard texture!\n");
//		return false;
//	}
//	printf("successfully loaded checkerboard \n");
//
//	return true;
//}
void lRender()
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	//Calculate centered offsets
	GLfloat x = (SCR_W - gCheckerBoardTexture.textureWidth()) / 2.f;
	GLfloat y = (SCR_H - gCheckerBoardTexture.textureHeight()) / 2.f;

	//Render checkerboard texture
	gCheckerBoardTexture.render(x, y);

	//Update screen
	glutSwapBuffers();
}
void update() {

}
void runMainLoop(int val) {
	update();
	lRender();
	glutTimerFunc(15, runMainLoop, val);
}