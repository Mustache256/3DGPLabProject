#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
public:

	//Camera object constructor and its various overloaded versions
	Camera();
	Camera(glm::vec3 position, glm::vec3 ort, float angle, glm::vec3 rotAxis);
	//Camera object destructor
	~Camera();

	//Set camera's projection matrix function
	void SetCamera(glm::mat4 projection) { m_identityMat = projection; }
	//Get camera's projection matrix function
	glm::mat4 GetCamera() { return m_identityMat; }

private:

};

