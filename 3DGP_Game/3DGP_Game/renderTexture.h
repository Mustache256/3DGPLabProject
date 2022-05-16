#pragma once
#include <GL/glew.h>

struct RenderTexture
{
	RenderTexture();
	RenderTexture(int _width, int _height);
	//RenderTexture(int _width, int _height, WfModel _model);
	~RenderTexture();

	void Bind();
	void Unbind();
	GLuint GetTexture();

private:
	GLuint m_fboId;
	GLuint m_texId;
	GLuint m_rboId;
	//WfModel m_model;
};