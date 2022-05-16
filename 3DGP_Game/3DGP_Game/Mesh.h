#pragma once
#include <GL/glew.h>

struct Mesh
{
	Mesh();
	Mesh(int _type);
	GLuint getId();
	int vertCount();
private:
	GLuint m_vaoId;
	GLuint m_posVboId;
};