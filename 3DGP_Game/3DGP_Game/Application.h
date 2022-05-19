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
	//Application construtor and destructor definitions
	Application();
	~Application();

	//Main game update function definition
	void update();
	//Function definition for the function that creates a new SDL window
	SDL_Window* RenderWindow();
	//Function definition for the function that creates a new Game Object
	void CreateSceneObject(glm::vec3 pos, glm::vec3 ort, glm::vec3 scale, float angle, glm::vec3 rotAxis, const char* filePath, GameObject::ObjectType type);
	//Function definition for the function that handles object rendering
	void Render(int i);

private:
	//SDL window object 
	SDL_Window* m_window;

	//Vector that stores all game objects 
	std::vector<SceneObject*> m_objects;

	//Main camera object 
	Camera* m_mainCamera;
	//Movement manager object 
	Movement* m_objMovement;

	//Quad mesh object
	Mesh* m_quadMesh;
	//Lighting shader object 
	Shader* m_lightShader;
	//Basic shader object
	Shader* m_basicShader;
	//Render texture object
	RenderTexture* m_renderTexture;

	//Model location storage variable
	GLint m_modelLoc;
	//Projection location storage variable
	GLint m_projectionLoc;

	//Quit check variable
	bool m_quitCheck;
	//Random seed manager variable
	bool m_randomGen;
	//Movement check storage variable
	int m_movementCheck;
};

