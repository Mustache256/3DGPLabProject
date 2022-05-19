#include "Application.h"
#include "renderTexture.h"
#include "Mesh.h"
#include "Shader.h"
#include "Movement.h"
#include "GameObject.h"
#include "Camera.h"
#include "SceneObject.h"

//Application object constructor
Application::Application()
{
	//Create new SDL window
	m_window = RenderWindow();

	//Create new perspective matrix to act as main game camera
	m_mainCamera = new Camera(glm::vec3(0.0f, -10.0f, -7.0f), glm::vec3(40.0f, 0.0f, 0.0f), 40.0f, glm::vec3(1, 0, 0));
	//Create new movemnt manager object
	m_objMovement = new Movement();

	//Create new rendering mesh object
	m_quadMesh = new Mesh();
	//Create new lighting shader renderer object
	m_lightShader = new Shader("vertexShaderText.txt", "fragmentShaderText.txt");
	//Create new basic shader renderer object
	m_basicShader = new Shader("basicVertexShaderText.txt", "basicFragmentShaderText.txt");
	//Create new render texture object
	m_renderTexture = new RenderTexture(1024, 1024);

	//Get and store lighting shader model and projection program ID's for use in rendering
	m_modelLoc = glGetUniformLocation(m_lightShader->getProgId(), "u_Model");
	m_projectionLoc = glGetUniformLocation(m_lightShader->getProgId(), "u_Projection");

	//Set quit check bool to the correct value upon making a new application object to ensure the game loop functions
	m_quitCheck = false;
	//Set movemnt check int to 0 by default
	m_movementCheck = 0;

	//Set random generator bool to correct value to make sure random generator is only seeded once
	m_randomGen = false;

	//Create player character object
	CreateSceneObject(glm::vec3(0.0f, 0.0f, -20.0f), glm::vec3(0.0f), glm::vec3(1.0f), 90.0f, glm::vec3(0, 1, 0), "models/curuthers/curuthers.obj", GameObject::ObjectType::Player);

	//Loop that creates all the floor objects for the game
	for (float i = -20.0f; i < 20.0f; i += 10.0f)
	{
		CreateSceneObject(glm::vec3(i, -2.5f, -20.0f), glm::vec3(0.0f), glm::vec3(2.0f, 1.0f, 1.0f), 90.0f, glm::vec3(0, 1, 0), "models/woodfloor/woodfloor.obj", GameObject::ObjectType::Floor);
	}

	//Creating the 6 enemy objects for the game
	CreateSceneObject(glm::vec3(20.0f, 1.0f, -24.0f), glm::vec3(0.0f), glm::vec3(1.0f), 90.0f, glm::vec3(0, 1, 0), "models/sphere/sphere.obj", GameObject::ObjectType::Enemy);
	CreateSceneObject(glm::vec3(25.0f, 1.0f, -20.0f), glm::vec3(0.0f), glm::vec3(1.0f), 90.0f, glm::vec3(0, 1, 0), "models/sphere/sphere.obj", GameObject::ObjectType::Enemy);
	CreateSceneObject(glm::vec3(30.0f, 1.0f, -16.0f), glm::vec3(0.0f), glm::vec3(1.0f), 90.0f, glm::vec3(0, 1, 0), "models/sphere/sphere.obj", GameObject::ObjectType::Enemy);
	CreateSceneObject(glm::vec3(35.0f, 1.0f, -24.0f), glm::vec3(0.0f), glm::vec3(1.0f), 90.0f, glm::vec3(0, 1, 0), "models/sphere/sphere.obj", GameObject::ObjectType::Enemy);
	CreateSceneObject(glm::vec3(40.0f, 1.0f, -20.0f), glm::vec3(0.0f), glm::vec3(1.0f), 90.0f, glm::vec3(0, 1, 0), "models/sphere/sphere.obj", GameObject::ObjectType::Enemy);
	CreateSceneObject(glm::vec3(45.0f, 1.0f, -16.0f), glm::vec3(0.0f), glm::vec3(1.0f), 90.0f, glm::vec3(0, 1, 0), "models/sphere/sphere.obj", GameObject::ObjectType::Enemy);

	//Set the positions of all the enemies to be accurate after they have been rotated during creation, this ensured collision detection functions
	m_objects.at(5)->SetPosition(glm::vec3(4.0f, 1.0f, -24.0f));
	m_objects.at(6)->SetPosition(glm::vec3(0.0f, 1.0f, -24.0f));
	m_objects.at(7)->SetPosition(glm::vec3(-4.0f, 1.0f, -24.0f));
	m_objects.at(8)->SetPosition(glm::vec3(4.0f, 1.0f, -24.0f));
	m_objects.at(9)->SetPosition(glm::vec3(0.0f, 1.0f, -24.0f));
	m_objects.at(10)->SetPosition(glm::vec3(-4.0f, 1.0f, -24.0f));
}

//Application object destructor
Application::~Application()
{
	//Destroy created window on destruct
	SDL_DestroyWindow(m_window);
}

//Function that handles SDL window creation and glew initialisation
SDL_Window* Application::RenderWindow()
{
	//Create new SDL window
	SDL_Window* window = SDL_CreateWindow("OpenGL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	//Check to ensure window was made successfully
	if (!SDL_GL_CreateContext(window))
	{
		throw std::runtime_error("Failed to create OpenGL context");
	}

	//Check to ensure glew is initialised successfully
	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to initialise glew");
	}

	//Return the created window
	return window;
}

//Function that handles new game object creation
void Application::CreateSceneObject(glm::vec3 pos, glm::vec3 ort, glm::vec3 scale, float angle, glm::vec3 rotAxis, const char* filePath, GameObject::ObjectType type)
{
	//Create new game object and push it into the game object vector
	SceneObject* newObj = new SceneObject(pos, ort, scale, angle, rotAxis, filePath, type);
	m_objects.push_back(newObj);
}

//Function that handles rendering to the scene
void Application::Render(int i)
{
	//Specify viewport dimensions
	glViewport(0, 0, 1024, 1024);

	//Bind created render texture
	m_renderTexture->Bind();

	//Set background colour of the scene only when rendering the first object
	if (i < 1)
	{
		//Clear red
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	//Make sure the current program is bound
	glUseProgram(m_lightShader->getProgId());
	//Bind vertex array from mesh quad and bind th texture from the current model being rendered 
	glBindVertexArray(m_quadMesh->getId());
	glBindTexture(GL_TEXTURE_2D, m_objects.at(i)->GetModelTexId());

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Upload the model matrix
	glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(m_objects.at(i)->GetIdentity()));

	// Upload the projection matrix
	glUniformMatrix4fv(m_projectionLoc, 1, GL_FALSE, glm::value_ptr(m_mainCamera->GetCamera()));

	// Instruct OpenGL to use our shader program and our VAO
	glBindVertexArray(m_objects.at(i)->GetModelVaoId());

	// Draw 3 vertices (a triangle)
	glDrawArrays(GL_TRIANGLES, 0, m_objects.at(i)->GetModelVertexCount());

	//Clear both the vertex array and program binds
	glBindVertexArray(0);
	glUseProgram(0);
	
	//Specify viewport dimensions
	glViewport(0, 0, 800, 600);

	//Unbind the render texture
	m_renderTexture->Unbind();

	//Clear Blue
	glClearColor(0.0f, 0.0f, 1.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Function calls that draw triangles
	glUseProgram(m_basicShader->getProgId());
	glBindVertexArray(m_quadMesh->getId());
	glBindTexture(GL_TEXTURE_2D, m_renderTexture->GetTexture());
	glDrawArrays(GL_TRIANGLES, 0, m_quadMesh->vertCount());
}

void Application::update()
{
	//Main game while loop
	while (!m_quitCheck)
	{
		//Retrieve quitCheck and movementCheck values from associated objects to see if either the game loop needs to end or if the player has input a move
		m_quitCheck = m_objMovement->GetQuit();
		m_movementCheck = m_objMovement->Move();

		//If statement that ensures random generator is only seeded once
		if (!m_randomGen)
		{
			//Seeding the generator
			m_randomGen = true;
			srand(time(NULL));
		}

		//For loops that updates all objects in the scene
		for (size_t i = 0; i < m_objects.size(); i++)
		{
			//Switch statement used to determine what updates need to be done to the current object being updated baed off of its type
			switch (m_objects.at(i)->GetType())
			{
				//Case for the player object
				case GameObject::ObjectType::Player:
				{
					//Switch statemnt that manages moving the player object
					switch (m_movementCheck)
					{
					//Case for moving the player left
					case 1:
					{
						//If statement that ensures the player cannot move out of the screen/off of the floor
						if (m_objects.at(i)->GetPosition().z > -27.0f) { m_objects.at(0)->TranslateObject(glm::vec3(0, 0, -0.3f)); }
					}
						break;
					//Case for moving the player right
					case 2:
					{
						//If statement that ensures the player cannot move out of the screen/off of the floor
						if (m_objects.at(i)->GetPosition().z < -12.0f) { m_objects.at(0)->TranslateObject(glm::vec3(0, 0, 0.3f)); }
					}
						break;
					//Case for moving the player up
					case 3:
					{
						//If statement that ensures the player cannot move out of the screen/off of the floor
						if (m_objects.at(i)->GetPosition().x < 8.0f) { m_objects.at(0)->TranslateObject(glm::vec3(0.3f, 0, 0)); }
					}
						break;
					//Case for moving the player down
					case 4:
					{
						//If statement that ensures the player cannot move out of the screen/off of the floor
						if (m_objects.at(i)->GetPosition().x > -9.0f) { m_objects.at(0)->TranslateObject(glm::vec3(-0.3f, 0, 0)); }
					}
						break;
					default:
						break;
					}
				}
				break;
				//Case for the floor objects
				case GameObject::ObjectType::Floor:
				{
					//Translate all the floor objects left to create infinite runner effect
					m_objects.at(i)->TranslateObject(glm::vec3(0, 0, -0.1f));
					//For loop and if statement that handles resetting the floors position to the right once they have gone off the screen to the left, to create the infinite runner effect
					for (size_t i = 0; i < 4; i++)
					{
						if (m_objects.at(i + 1)->GetPosition().z < -20.0f - (i * 10))
						{
							m_objects.at(i + 1)->TranslateObject(glm::vec3(0, 0, 40.0f));
						}
					}
				}
				break;
				//Case for the enemy objects
				case GameObject::ObjectType::Enemy:
				{
					//Translate all the floor objects left to create infinite runner effect
					m_objects.at(i)->TranslateObject(glm::vec3(0, 0, -0.1f));
					//For loop that ensures all the enemies are updated
					for (size_t i = 0; i < 6; i++)
					{
						//Check that resets the enemies to the right when the go off-screen to the left to create infinite runner effect, randomising their z position so that they will reappear in an uneven order
						if (m_objects.at(i + 5)->GetPosition().z < -70.0f - (i * 5))
						{
							m_objects.at(i + 5)->TranslateObject(glm::vec3(0, 0, 50.0f * (rand() % 2 + 1)));
						}

						//if staement/nested if statement that handled collision detection between the player and the enemy objects
						if ((m_objects.at(0)->GetPosition().z - (23.5f + i * 5.0f)) < (m_objects.at(i + 5)->GetPosition().z + 1.1f) && (m_objects.at(0)->GetPosition().z - (23.5f + i * 5.0f)) > (m_objects.at(i + 5)->GetPosition().z - 1.1f))
						{
							if ((m_objects.at(0)->GetPosition().x < (m_objects.at(i + 5)->GetPosition().x + 2.0f) && (m_objects.at(0)->GetPosition().x > (m_objects.at(i + 5)->GetPosition().x - 2.0f))))
							{
								//Exit game loop if an enemy collided with the player
								m_quitCheck = true;
							}
						}
					}
				}
				break;
			}
		}
		
		//Enable backface culling, blending and depth testing
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		//Render all the objects onto the scene 
		for (int i = 0; i < m_objects.size(); i++)
		{
			Render(i);
		}

		//Disable backface culling, blending and depth testing
		glDisable(GL_BLEND);
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		//Update the SDL window
		SDL_GL_SwapWindow(m_window);
	}
}