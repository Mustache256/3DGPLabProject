#include <wavefront/wavefront.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "window.h"

#include <stdexcept>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

const GLchar * vertexShaderSrc =
"uniform mat4 u_Projection;                                       " \
"uniform mat4 u_Model;                                            " \
"attribute vec3 a_Position;                                       " \
"attribute vec2 a_TexCoord;                                       " \
"varying vec2 v_TexCoord;                                         " \
"                                                                 " \
"void main()                                                      " \
"{                                                                " \
"  gl_Position = u_Projection * u_Model * vec4(a_Position, 1.0);  " \
"  v_TexCoord = a_TexCoord;                                       " \
"}                                                                " \
"                                                                 ";

const GLchar* fragmentShaderSrc =
"uniform sampler2D u_Texture;                       " \
"varying vec2 v_TexCoord;                           " \
"void main()                                        " \
"{                                                  " \
"  gl_FragColor = texture2D(u_Texture, v_TexCoord); " \
"}                                                  " \
"                                                   ";

int main(int argc, char* argv[])
{
	Window window;

	/***********************************************************************
	 * Prepare Shader Program
	 ***********************************************************************/
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::runtime_error("Failed to compile vertex shader");
	}

	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::runtime_error("Failed to compile fragment shader");
	}

	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glBindAttribLocation(programId, 0, "a_Position");
	glBindAttribLocation(programId, 1, "a_TexCoord");

	glLinkProgram(programId);
	glGetProgramiv(programId, GL_LINK_STATUS, &success);

	if (!success)
	{
		throw std::runtime_error("Failed to link shader program");
	}

	glDetachShader(programId, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(programId, fragmentShaderId);
	glDeleteShader(fragmentShaderId);

	GLint projectionLoc = glGetUniformLocation(programId, "u_Projection");
	GLint modelLoc = glGetUniformLocation(programId, "u_Model");

	WfModel curuthers = { 0 };

	if (WfModelLoad("models/curuthers/curuthers.obj", &curuthers) != 0)
	{
		throw std::runtime_error("Failed to load model");
	}

	/***********************************************************************
	 * Loop
	 ***********************************************************************/
	bool quit = false;
	float angle = 0;

	while (!quit)
	{
		SDL_Event event = { 0 };

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);
		glUseProgram(programId);

		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(glm::perspective(
			glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f)));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(glm::rotate(
			glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f)), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f))));

		angle++;

		glBindVertexArray(curuthers.vaoId);
		glBindTexture(GL_TEXTURE_2D, curuthers.textureId);

		glDrawArrays(GL_TRIANGLES, 0, curuthers.vertexCount);

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		glUseProgram(0);

		glDisable(GL_DEPTH_TEST);

		window.Swap();
	}

	WfModelDestroy(&curuthers);

	return 0;
}

