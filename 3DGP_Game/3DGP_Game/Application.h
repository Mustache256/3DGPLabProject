#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <stb_image.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <vector>
#include <random>
#include "GameObject.h"

class RenderTexture;
class Mesh;
class Shader;
class Movement;
class GameObject;
class Camera;
class SceneObject;
class Enemy;

class Application
{
public:

	Application();
	~Application();
	void update();
	SDL_Window* RenderWindow();
	void CreateSceneObject(glm::vec3 pos, glm::vec3 ort, glm::vec3 scale, float angle, glm::vec3 rotAxis, const char* filePath, GameObject::ObjectType type);
	void Render(int i);

private:

	SDL_Window* m_window;

	std::vector<SceneObject*> m_sceneObjects;

	Camera* m_camera;
	Movement* m_movement;

	Mesh* m_quad;
	Shader* m_lightShader;
	Shader* m_basicShader;
	RenderTexture* m_renderTexture;

	GLint m_modelLoc;
	GLint m_projectionLoc;

	bool m_quit;
	bool m_randGen;
	int m_moveCheck;
};

