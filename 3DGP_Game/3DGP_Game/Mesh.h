#pragma once
#include <GL/glew.h>

class Mesh
{
public:
	//Mesh constructor
	Mesh();
	//Get ID function
	GLuint getId();
	//Function that returns the mesh vertex count
	int vertCount();
private:
	//Mesh vertex array object ID storage variable
	GLuint m_vaoId;
	//Mesh position vertex buffer object ID storage variable
	GLuint m_posVboId;
};