#include "LTexture.h"
#include <IL/il.h>

#include <string>
#include "SOIL.h"

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
//bool LTexture::loadTextureFromPixels32(GLuint* pixels, GLuint width, GLuint height) {
//	//Free texture if it exists
//	freeTexture();
//
//	//Get texture dimensions
//	mTextureWidth = width;
//	mTextureHeight = height;
//	glGenTextures(1, &mTextureID);
//
//	//Bind texture ID
//	glBindTexture(GL_TEXTURE_2D, mTextureID);
//	//Generate texture
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
//	//Set texture parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	//Unbind texture
//	glBindTexture(GL_TEXTURE_2D, NULL);
//
//	//Check for error
//	GLenum error = glGetError();
//	if (error != GL_NO_ERROR)
//	{
//		printf("Error loading texture from %p pixels! %s\n", pixels, gluErrorString(error));
//		return false;
//	}
//
//	return true;
//}
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
		glTexCoord2f(0.5f, 0.f); glVertex2f(mTextureWidth/2, 0.f);
		glTexCoord2f(0.5f, 1.f); glVertex2f(mTextureWidth/2, mTextureHeight);
		glTexCoord2f(0.f, 1.f); glVertex2f(0.f, mTextureHeight);
		glEnd();
		
		
	}
	//glutSwapBuffers();
}

GLuint LTexture::getTextureID()
{
	return mTextureID;
}

GLint LTexture::textureWidth()
{
	return mTextureWidth;
}

GLint LTexture::textureHeight()
{
	return mTextureHeight;
}
bool LTexture::loadTextureFromFile(std::string path) {
	printf("loading image from file,hahah\n");
	bool textureLoaded = false;

	//ILuint imgID = 0;
	//ilGenImages(1, &imgID);
	//ilBindImage(imgID);
	//printf("image id is %d\n", imgID);
	//fflush(stdout);
	//std::wstring ws;
	//ws.assign(path.begin(), path.end());
	//printf("loading texture\n");
	//ILboolean success = ilLoadImage(L"f:/Practice/CPP/Floral/texture.png");
	//printf("loaded texture\n");
	//printf("loaded returned code is %d haha\n", (int)success);
	//if (success == IL_TRUE)
	//{
	//	printf("successfully loaded file\n");
	//	//convert image to RGBA
	//	success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	//	if (success ==IL_TRUE) {
	//		printf("successfully converted file\n");
	//		textureLoaded = loadTextureFromPixels32((GLuint*)ilGetData(), (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT));
	//	}
	//	else {
	//		printf("failed to convert file\n");
	//	}
	//	ilDeleteImages(1, &imgID);
	//}else {
	//	ILenum err=ilGetError();
	//	printf("error code is %d\n", (int)err);
	//	printf("failed to load the image file at loadTextureFromFile\n");
	//}
	////report error
	//if (!textureLoaded) {
	//	printf("Unable to load %s\n", path.c_str());
	//}
	mTextureID = SOIL_load_OGL_texture(
			"texture.jpg",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
	if (0 == mTextureID) {
		printf("SOIL loading error: %s\n", SOIL_last_result());
		return false;
	}
	else {
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &mTextureWidth);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &mTextureHeight);
		return true;
	}
}
