#pragma once
#include <wavefront/wavefront.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>

class GameObject abstract
{
public:

	enum class ObjectType { Player, Enemy, Floor, Other };

	virtual void SetPosition(glm::vec3 pos) { m_position = pos; }
	virtual glm::vec3 GetPosition() { return m_position; }

	virtual void SetOrientation(glm::vec3 ort) { m_orientation = ort; }
	virtual glm::vec3 GetOrientation() { return m_orientation; }

	virtual void SetIdentity(glm::mat4 identity) { m_identity = identity; }
	virtual glm::mat4 GetIdentity() { return m_identity; }

	virtual void SetType(ObjectType type) { m_type = type; }
	virtual ObjectType GetType() { return m_type; }

	virtual void TranslateObject(glm::vec3 translation);
	virtual void RotateObject(float angle, glm::vec3 rotAxis);

protected:
	
	glm::vec3 m_position = glm::vec3(0.0f);
	glm::vec3 m_orientation = glm::vec3(0.0f);
	glm::mat4 m_identity = glm::mat4(0.0f);
	ObjectType m_type;
};

