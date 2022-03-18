#pragma once
#include <GL/glew.h>

struct PositionsVBO
{
	PositionsVBO();
	~PositionsVBO();

	void bind();
	void unbind();
	GLuint getPositionsVbo();
private:
	GLuint m_positionsVboId;
};