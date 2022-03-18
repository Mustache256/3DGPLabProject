#include <GL/glew.h>
#include <iostream>
#include "positionsVBO.h"

const GLfloat positions[] = {
	0.0f, 0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f
};

PositionsVBO::PositionsVBO()
{
	// Create a new VBO on the GPU and bind it
	glGenBuffers(1, &m_positionsVboId);

	if (!m_positionsVboId)
	{
		throw std::exception();
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_positionsVboId);

	// Upload a copy of the data from memory into the new VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	// Reset the state
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

PositionsVBO::~PositionsVBO()
{

}

void PositionsVBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_positionsVboId);
}

void PositionsVBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint getPositionsVbo()
{
	return m_positionsVboId;
}