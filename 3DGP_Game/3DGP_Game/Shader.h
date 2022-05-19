#pragma once
#include <GL/glew.h>
#include <string>

class Shader
{
public:
	//Shader constructor and its overloaded version
	Shader();
	Shader(const std::string& _vertPath, const std::string& _fragPath);

	//Get program ID function
	GLuint getProgId();
private:
	//Program ID storage variable
	GLuint m_progId;
};