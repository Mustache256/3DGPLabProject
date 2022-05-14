#pragma once
#include <GL/glew.h>
#include <string>

struct Shader
{
	Shader(const std::string& _vertPath, const std::string& _fragPath);

	GLuint getProgId();
private:
	GLuint m_progId;
};