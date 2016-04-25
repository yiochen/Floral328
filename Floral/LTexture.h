#pragma once
#include "opengl_include.h"
#include <string>
class LTexture
{
public:
	LTexture();
	~LTexture();
	void init();
	bool loadTextureFromFile(std::string path);
	bool loadTextureFromPixels32(GLuint* pixels, GLuint width, GLuint height);
	void freeTexture();
	void render(GLfloat x, GLfloat y);
	
	GLuint getTextureID();
	GLuint textureWidth();
	GLuint textureHeight();
private:
	GLuint mTextureID;
	GLuint mTextureWidth;
	GLuint mTextureHeight;
};

