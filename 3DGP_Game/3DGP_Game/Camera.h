#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
public:

	Camera();
	Camera(glm::vec3 position, glm::vec3 ort, float angle, glm::vec3 rotAxis);
	~Camera();

	void SetCamera(glm::mat4 projection) { m_identity = projection; }
	glm::mat4 GetCamera() { return m_identity; }

private:

};
