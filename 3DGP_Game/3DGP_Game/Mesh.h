#pragma once
#include <GL/glew.h>

class Mesh
{
public:
	Mesh();
	Mesh(int _type);
	GLuint getId();
	int vertCount();
private:
	GLuint m_vaoId;
	GLuint m_posVboId;
};