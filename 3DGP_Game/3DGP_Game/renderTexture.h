#pragma once
#include <GL/glew.h>

class RenderTexture
{
public:
	//Render Texture constructor and its overloaded version
	RenderTexture();
	RenderTexture(int _width, int _height);
	//Rendder Texture destructor
	~RenderTexture();

	//Function for binding the Render Texture
	void Bind();
	//Function for unbinding the Render Texture
	void Unbind();
	//Function for getting the Render Texture
	GLuint GetTexture();

private:
	//Render Texture frame buffer object ID storage vector
	GLuint m_fboId;
	//Render Texture texture ID storage vector
	GLuint m_texId;
	//Render Texture render buffer object ID storage vector
	GLuint m_rboId;
};