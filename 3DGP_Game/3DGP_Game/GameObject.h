#pragma once
#include <wavefront/wavefront.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class GameObject abstract
{
public:

	virtual void SetPosition(glm::vec3 pos) { m_position = pos; }
	virtual glm::vec3 GetPosition() { return m_position; }

	virtual void SetOrientation(glm::vec3 ort) { m_orientation = ort; }
	virtual glm::vec3 GetOrientation() { return m_orientation; }

	virtual void SetIdentity(glm::mat4 identity) { m_identity = identity; }
	virtual glm::mat4 GetIdentity() { return m_identity; }

	virtual void TranslateObject(glm::vec3 translation);
	virtual void RotateObject(float angle, glm::vec3 rotAxis);

protected:
	
	glm::vec3 m_position = glm::vec3(0.0f);
	glm::vec3 m_orientation = glm::vec3(0.0f);
	glm::mat4 m_identity = glm::mat4(0.0f);
};

