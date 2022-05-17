#include "Application.h"
#include "renderTexture.h"
#include "Mesh.h"
#include "Shader.h"
#include "Movement.h"
#include "GameObject.h"
#include "Camera.h"
#include "SceneObject.h"

Application::Application()
{
	m_window = RenderWindow();

	m_camera = new Camera(glm::vec3(0.0f, -5.0f, -10.0f), glm::vec3(10.0f, 0.0f, 0.0f), 10.0f, glm::vec3(1, 0, 0));
	m_movement = new Movement();

	m_quad = new Mesh(0);
	m_lightShader = new Shader("vertexShaderText.txt", "fragmentShaderText.txt");
	m_basicShader = new Shader("basicVertexShaderText.txt", "basicFragmentShaderText.txt");
	m_renderTexture = new RenderTexture(1024, 1024);

	m_modelLoc = glGetUniformLocation(m_lightShader->getProgId(), "u_Model");
	m_projectionLoc = glGetUniformLocation(m_lightShader->getProgId(), "u_Projection");

	m_quit = false;
	m_moveCheck = 0;

	CreateSceneObject(glm::vec3(0.0f, 0.0f, -20.0f), glm::vec3(0.0f), 90.0f, glm::vec3(0, 1, 0), "models/curuthers/curuthers.obj");
	CreateSceneObject(glm::vec3(2.0f, 0.0f, -10.0f), glm::vec3(0.0f), 0.0f, glm::vec3(0, 1, 0), "models/sphere/sphere.obj");
	CreateSceneObject(glm::vec3(0.0f, -2.5f, -10.0f), glm::vec3(0.0f), 0.0f, glm::vec3(0, 1, 0), "models/woodfloor/woodfloor.obj");
	CreateSceneObject(glm::vec3(0.0f, -2.5f, -20.0f), glm::vec3(0.0f), 0.0f, glm::vec3(0, 1, 0), "models/woodfloor/woodfloor.obj");
	CreateSceneObject(glm::vec3(0.0f, -2.5f, -30.0f), glm::vec3(0.0f), 0.0f, glm::vec3(0, 1, 0), "models/woodfloor/woodfloor.obj");

	CreateSceneObject(glm::vec3(-10.0f, -2.5f, -10.0f), glm::vec3(0.0f), 0.0f, glm::vec3(0, 1, 0), "models/woodfloor/woodfloor.obj");
	CreateSceneObject(glm::vec3(-10.0f, -2.5f, -20.0f), glm::vec3(0.0f), 0.0f, glm::vec3(0, 1, 0), "models/woodfloor/woodfloor.obj");
	CreateSceneObject(glm::vec3(-10.0f, -2.5f, -30.0f), glm::vec3(0.0f), 0.0f, glm::vec3(0, 1, 0), "models/woodfloor/woodfloor.obj");

	CreateSceneObject(glm::vec3(10.0f, -2.5f, -10.0f), glm::vec3(0.0f), 0.0f, glm::vec3(0, 1, 0), "models/woodfloor/woodfloor.obj");
	CreateSceneObject(glm::vec3(10.0f, -2.5f, -20.0f), glm::vec3(0.0f), 0.0f, glm::vec3(0, 1, 0), "models/woodfloor/woodfloor.obj");
	CreateSceneObject(glm::vec3(10.0f, -2.5f, -30.0f), glm::vec3(0.0f), 0.0f, glm::vec3(0, 1, 0), "models/woodfloor/woodfloor.obj");

	CreateSceneObject(glm::vec3(-20.0f, -2.5f, -10.0f), glm::vec3(0.0f), 0.0f, glm::vec3(0, 1, 0), "models/woodfloor/woodfloor.obj");
	CreateSceneObject(glm::vec3(-20.0f, -2.5f, -20.0f), glm::vec3(0.0f), 0.0f, glm::vec3(0, 1, 0), "models/woodfloor/woodfloor.obj");
	CreateSceneObject(glm::vec3(-20.0f, -2.5f, -30.0f), glm::vec3(0.0f), 0.0f, glm::vec3(0, 1, 0), "models/woodfloor/woodfloor.obj");

	CreateSceneObject(glm::vec3(20.0f, -2.5f, -10.0f), glm::vec3(0.0f), 0.0f, glm::vec3(0, 1, 0), "models/woodfloor/woodfloor.obj");
	CreateSceneObject(glm::vec3(20.0f, -2.5f, -20.0f), glm::vec3(0.0f), 0.0f, glm::vec3(0, 1, 0), "models/woodfloor/woodfloor.obj");
	CreateSceneObject(glm::vec3(20.0f, -2.5f, -30.0f), glm::vec3(0.0f), 0.0f, glm::vec3(0, 1, 0), "models/woodfloor/woodfloor.obj");
}

Application::~Application()
{
	SDL_DestroyWindow(m_window);
}

SDL_Window* Application::RenderWindow()
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

	return window;
}

void Application::CreateSceneObject(glm::vec3 pos, glm::vec3 ort, float angle, glm::vec3 rotAxis, const char* filePath)
{
	SceneObject* newObj = new SceneObject(pos, ort, angle, rotAxis, filePath);
	m_sceneObjects.push_back(newObj);
}

void Application::Render(int i)
{
	glViewport(0, 0, 1024, 1024);

	m_renderTexture->Bind();

	if (i < 1)
	{
		//Clear red
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Make sure the current program is bound
	}

	glUseProgram(m_lightShader->getProgId());
	glBindVertexArray(m_quad->getId());
	glBindTexture(GL_TEXTURE_2D, m_sceneObjects.at(i)->GetModelTexId());

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Upload the model matrix
	glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(m_sceneObjects.at(i)->GetIdentity()));

	// Upload the projection matrix
	glUniformMatrix4fv(m_projectionLoc, 1, GL_FALSE, glm::value_ptr(m_camera->GetCamera()));

	// Instruct OpenGL to use our shader program and our VAO
	glBindVertexArray(m_sceneObjects.at(i)->GetModelVaoId());

	// Draw 3 vertices (a triangle)
	glDrawArrays(GL_TRIANGLES, 0, m_sceneObjects.at(i)->GetModelVertexCount());

	glBindVertexArray(0);
	glUseProgram(0);
	
	glViewport(0, 0, 800, 600);

	m_renderTexture->Unbind();

	//Clear Blue
	glClearColor(0.0f, 0.0f, 1.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_basicShader->getProgId());
	glBindVertexArray(m_quad->getId());
	glBindTexture(GL_TEXTURE_2D, m_renderTexture->GetTexture());
	glDrawArrays(GL_TRIANGLES, 0, m_quad->vertCount());
}

void Application::update()
{
	while (!m_quit)
	{
		m_quit = m_movement->GetQuit();
		m_moveCheck = m_movement->Move();

		switch (m_moveCheck)
		{
		case 1:
			m_sceneObjects.at(0)->TranslateObject(glm::vec3(0, 0, -0.5f));
			break;
		case 2:
			m_sceneObjects.at(0)->TranslateObject(glm::vec3(0, 0, 0.5f));
			break;
		case 3:
			m_sceneObjects.at(0)->TranslateObject(glm::vec3(0.5f, 0, 0));
			break;
		case 4:
			m_sceneObjects.at(0)->TranslateObject(glm::vec3(-0.5f, 0, 0));
			break;
		default:
			break;
		}

		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		for (int i = 0; i < m_sceneObjects.size(); i++)
		{
			Render(i);
		}

		glDisable(GL_BLEND);
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		SDL_GL_SwapWindow(m_window);
	}
}