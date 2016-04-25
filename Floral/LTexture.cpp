#include "LTexture.h"
#include <IL/il.h>

#include <string>


LTexture::LTexture()
{
	//Initialize texture ID
	mTextureID = 0;

	//Initialize texture dimensions
	mTextureWidth = 0;
	mTextureHeight = 0;
	//Generate texture ID
	
}


LTexture::~LTexture()
{
}

void LTexture::init() {

}
bool LTexture::loadTextureFromPixels32(GLuint* pixels, GLuint width, GLuint height) {
	//Free texture if it exists
	freeTexture();

	//Get texture dimensions
	mTextureWidth = width;
	mTextureHeight = height;
	glGenTextures(1, &mTextureID);

	//Bind texture ID
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	//Generate texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//Unbind texture
	glBindTexture(GL_TEXTURE_2D, NULL);

	//Check for error
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error loading texture from %p pixels! %s\n", pixels, gluErrorString(error));
		return false;
	}

	return true;
}
void LTexture::freeTexture() {
	//Delete texture
	if (mTextureID != 0)
	{
		glDeleteTextures(1, &mTextureID);
		mTextureID = 0;
	}

	mTextureWidth = 0;
	mTextureHeight = 0;
}
void LTexture::render(GLfloat x, GLfloat y) {
	//If the texture exists
	if (mTextureID != 0)
	{
		//Remove any previous transformations
		glLoadIdentity();

		//Move to rendering point
		glTranslatef(x, y, 0.f);

		//Set texture ID
		glBindTexture(GL_TEXTURE_2D, mTextureID);
		//Render textured quad
		glBegin(GL_QUADS);
		glTexCoord2f(0.f, 0.f); glVertex2f(0.f, 0.f);
		glTexCoord2f(1.f, 0.f); glVertex2f(mTextureWidth, 0.f);
		glTexCoord2f(1.f, 1.f); glVertex2f(mTextureWidth, mTextureHeight);
		glTexCoord2f(0.f, 1.f); glVertex2f(0.f, mTextureHeight);
		glEnd();
		
		
	}
	glutSwapBuffers();
}

GLuint LTexture::getTextureID()
{
	return mTextureID;
}

GLuint LTexture::textureWidth()
{
	return mTextureWidth;
}

GLuint LTexture::textureHeight()
{
	return mTextureHeight;
}
bool LTexture::loadTextureFromFile(std::string path) {
	bool textureLoaded = false;

	ILuint imgID = 0;
	ilGenImages(1, &imgID);
	ilBindImage(imgID);
	std::wstring ws;
	ws.assign(path.begin(), path.end());
	ILboolean success = ilLoadImage(ws.c_str());
	if (success = IL_TRUE)
	{
		printf("successfully loaded file\n");
		//convert image to RGBA
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		if (success ==IL_TRUE) {
			printf("successfully converted file\n");
			textureLoaded = loadTextureFromPixels32((GLuint*)ilGetData(), (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT));
		}
		else {
			printf("failed to convert file\n");
		}
		ilDeleteImages(1, &imgID);
	}else {
		printf("failed to load the image file at loadTextureFromFile\n");
	}
	//report error
	if (!textureLoaded) {
		printf("Unable to load %s\n", path.c_str());
	}
	return textureLoaded;
}
