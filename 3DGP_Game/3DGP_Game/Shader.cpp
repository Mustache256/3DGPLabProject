#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "Shader.h"

//Function for reading and loading shader information from a file 
std::string loadFile(const std::string _path)
{
	//Get the file from the file path
	std::ifstream file(_path.c_str());

	//Check to make sure the file has opened properly
	if (!file.is_open())
	{
		throw std::exception("Failed to open file");
	}

	//Defining local storage variables
	std::string rtn;
	std::string line;

	//Read from file line by line and store the readout
	while (!file.eof())
	{
		std::getline(file, line);
		rtn += line + '\n';
	}
	//Return the file contents
	return rtn;
}


Shader::Shader()
{

}

Shader::Shader(const std::string& _vertPath, const std::string& _fragPath)
{
	/////////////////////////////////////////////////////
	//Vertex Shader
	/////////////////////////////////////////////////////
	//Create the vertex shader
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	//Store readout from file
	std::string src = loadFile(_vertPath);
	const char* psrc = src.c_str();
	//Set Shader source
	glShaderSource(vertexShaderId, 1, &psrc, NULL);
	//Compile vertex shader
	glCompileShader(vertexShaderId);

	GLint success = 0;

	//Check to see if the shader compiled correctly
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(vertexShaderId, maxLength, &maxLength, &errorLog[0]);
		std::cout << &errorLog.at(0) << std::endl;
		throw std::exception();
	}

	/////////////////////////////////////////////////////
	//Fragment Shader
	/////////////////////////////////////////////////////
	//Create the fragment shader
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	//Store readout from file
	src = loadFile(_fragPath);
	psrc = src.c_str();
	//Set Shader source
	glShaderSource(fragmentShaderId, 1, &psrc, NULL);
	//Compile fragment shader
	glCompileShader(fragmentShaderId);

	//Check to see if the shader compiled correctly
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(fragmentShaderId, maxLength, &maxLength, &errorLog[0]);
		std::cout << &errorLog.at(0) << std::endl;
		throw std::exception();
	}

	/////////////////////////////////////////////////////
	//Create Program
	/////////////////////////////////////////////////////
	//Create the program
	m_progId = glCreateProgram();
	//Attach both of the created shaders to the program
	glAttachShader(m_progId, vertexShaderId);
	glAttachShader(m_progId, fragmentShaderId);

	// Ensure the VAO "position" attribute stream gets set as the first position during the link.
	glBindAttribLocation(m_progId, 0, "a_Position");
	glBindAttribLocation(m_progId, 1, "a_TexCoord");
	glBindAttribLocation(m_progId, 2, "a_Normal");

	// Perform the link and check for failure
	glLinkProgram(m_progId);

	//Check to see if the binding and linking were successful
	glGetProgramiv(m_progId, GL_LINK_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}

	// Detach and destroy the shader objects. These are no longer needed because we now have a complete shader program.
	glDetachShader(m_progId, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(m_progId, fragmentShaderId);
	glDeleteShader(fragmentShaderId);
}

GLuint Shader::getProgId()
{
	//Return program ID
	return m_progId;
}