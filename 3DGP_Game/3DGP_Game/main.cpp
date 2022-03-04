#define SDL_MAIN_HANDLED
//#define STB_IMAGE_IMPLEMENTATION
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <stb_image.h>
#include <wavefront/wavefront.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <vector>

std::string fileRead(std::string fileName)
{
	std::string line;
	std::string fileString;
	std::ifstream fileRead(fileName);
	if (fileRead.is_open())
	{
		while (getline(fileRead, line))
		{
			std::cout << line << std::endl;
			fileString += line;
		}
	}
	else
	{
		std::cout << "File unable to open" << std::endl;
	}
	fileRead.close();

	return fileString;
}

int main()
{
	SDL_Window* window = SDL_CreateWindow("OpenGL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(window))
	{
		throw std::runtime_error("Failed to create OpenGL context");
	}

	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to initialise glew");
	}

	const GLfloat positions[] = {
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};

	const GLfloat colors[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
	};

	const GLfloat texCoords[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,

		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f
	};

	GLuint positionsVboId = 0;

	int w = 0;
	int h = 0;

	unsigned char* data = stbi_load("image.png", &w, &h, NULL, 4);

	if (!data)
	{
		throw std::exception();
	}

	// Create a new VBO on the GPU and bind it
	glGenBuffers(1, &positionsVboId);

	if (!positionsVboId)
	{
		throw std::exception();
	}

	glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);

	// Upload a copy of the data from memory into the new VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	// Reset the state
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint colorsVboId = 0;

	// Create a colors VBO on the GPU and bind it
	glGenBuffers(1, &colorsVboId);

	if (!colorsVboId)
	{
		throw std::exception();
	}

	glBindBuffer(GL_ARRAY_BUFFER, colorsVboId);

	// Upload a copy of the data from memory into the new VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	// Bind the color VBO, assign it to position 1 on the bound VAO
	// and flag it to be used
	GLuint texCoordsVboId = 0;

	//Texture stuff
	glGenBuffers(1, &texCoordsVboId);

	if (!texCoordsVboId)
	{
		throw std::exception();
	}

	glBindBuffer(GL_ARRAY_BUFFER, texCoordsVboId);

	// Upload a copy of the data from memory into the new VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	GLuint vaoId = 0;

	// Create a new VAO on the GPU and bind it
	glGenVertexArrays(1, &vaoId);

	if (!vaoId)
	{
		throw std::exception();
	}

	glBindVertexArray(vaoId);

	// Bind the position VBO, assign it to position 0 on the bound VAO
	// and flag it to be used
	glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, colorsVboId);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);

	glEnableVertexAttribArray(1);

	// Reset the state
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	std::string text = fileRead("vertexShaderText.txt");
	const GLchar* vertexShaderSrc = text.c_str();
	
	// Create a new vertex shader, attach source code, compile it and
	// check for errors.
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShaderId);

	GLint success = 0;

	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH,
			&maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(vertexShaderId, maxLength,
			&maxLength, &errorLog[0]);
		std::cout << &errorLog.at(0) << std::endl;
		throw std::exception();
	}

	text = fileRead("fragmentShaderText.txt");
	const GLchar* fragmentShaderSrc = text.c_str();

	// Create a new fragment shader, attach source code, compile it and
	// check for errors.
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH,
			&maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(fragmentShaderId, maxLength,
			&maxLength, &errorLog[0]);
		std::cout << &errorLog.at(0) << std::endl;
		throw std::exception();
	}

	// Create new shader program and attach our shader objects
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);

	// Ensure the VAO "position" attribute stream gets set as the first position
	// during the link.
	glBindAttribLocation(programId, 0, "a_Position");
	glBindAttribLocation(programId, 1, "a_TexCoord");


	// Perform the link and check for failure
	glLinkProgram(programId);
	glUseProgram(programId);

	glGetProgramiv(programId, GL_LINK_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}

	// Detach and destroy the shader objects. These are no longer needed
	// because we now have a complete shader program.
	glDetachShader(programId, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(programId, fragmentShaderId);
	glDeleteShader(fragmentShaderId);

	GLuint textureId = 0;
	glGenTextures(1, &textureId);
	if (!textureId)
	{
		std::cout << "NO TEXTURE ID FOUND" << std::endl;
		throw std::exception();
	}
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	free(data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	WfModel curuthers = { 0 };

	if (WfModelLoad("models/curuthers/curuthers.obj", &curuthers) != 0)
	{
		throw std::runtime_error("Failed to load model");
	}

	GLint modelLoc = glGetUniformLocation(programId, "u_Model");
	GLint projectionLoc = glGetUniformLocation(programId, "u_Projection");

	float angle = 0;
	bool quit = false;

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

		//Clear red
		glClearColor(0, 0.5f, 0.5f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Prepare the perspective projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)600 / (float)600, 0.1f, 100.f);

		// Prepare the model matrix
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0, 0, -20.5f));
		model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));

		// Increase the float angle so next frame the triangle rotates further
		angle += 1.0f;

		// Make sure the current program is bound

		glUseProgram(programId);
		glBindVertexArray(vaoId);
		glBindTexture(GL_TEXTURE_2D, curuthers.textureId);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Upload the model matrix
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		// Upload the projection matrix
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Instruct OpenGL to use our shader program and our VAO
		
		glBindVertexArray(curuthers.vaoId);
		//glBindTexture(GL_TEXTURE_2D, curuthers.vertexCount);

		// Draw 3 vertices (a triangle)
		glDrawArrays(GL_TRIANGLES, 0, curuthers.vertexCount);

		// Reset the state
		glDisable(GL_BLEND);
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glBindVertexArray(0);
		glUseProgram(0);

		//Update buffers
		SDL_GL_SwapWindow(window);
	}
	return 0;
}