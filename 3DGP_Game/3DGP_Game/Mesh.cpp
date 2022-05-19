#include <GL/glew.h>
#include <exception>

#include "Mesh.h"


const GLfloat positions[] = {
	-1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,

	1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f
};

Mesh::Mesh()
{
	//Generate mesh buffers
	glGenBuffers(1, &m_posVboId);

	//Check to make sure buffers were created successfully
	if (!m_posVboId)
	{
		throw std::exception();
	}

	//Bind the created buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_posVboId);

	// Upload a copy of the data from memory into the new VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	// Reset the state
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Create a new VAO on the GPU and bind it
	glGenVertexArrays(1, &m_vaoId);

	//Check to ensure the VAO was created successfully
	if (!m_vaoId)
	{
		throw std::exception();
	}

	//Bind the VAO
	glBindVertexArray(m_vaoId);

	//Bind the position VBO, assign it to position 0 on the bound VAO and flag it to be used
	glBindBuffer(GL_ARRAY_BUFFER, m_posVboId);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
}

GLuint Mesh::getId()
{
	//Return the VAO ID
	return m_vaoId;
}

int Mesh::vertCount()
{
	//Return the correct mesh vertex count
	return 6;
}