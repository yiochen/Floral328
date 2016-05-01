#pragma once
#include "opengl_include.h"
#include <string>

/*LTexture represent a texture read from file*/
class LTexture
{
public:
	LTexture();
	~LTexture();
	void init();
	bool loadTextureFromFile(std::string path);
	//bool loadTextureFromPixels32(GLuint* pixels, GLuint width, GLuint height);
	void freeTexture();
	void render(GLfloat x, GLfloat y);
	
	GLuint getTextureID();
	GLint textureWidth();
	GLint textureHeight();
private:
	GLuint mTextureID;
	GLint mTextureWidth;
	GLint mTextureHeight;
};

