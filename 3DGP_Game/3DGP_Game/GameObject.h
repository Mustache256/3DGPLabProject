#pragma once
#include <wavefront/wavefront.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>

class GameObject abstract
{
public:

	//Enum class for setting an objects type
	enum class ObjectType { Player, Enemy, Floor, Other };

	//Setter and getter for object position
	virtual void SetPosition(glm::vec3 pos) { m_objPos = pos; }
	virtual glm::vec3 GetPosition() { return m_objPos; }

	//Setter and getter for object orientation
	virtual void SetOrientation(glm::vec3 ort) { m_objOrt = ort; }
	virtual glm::vec3 GetOrientation() { return m_objOrt; }

	//Setter and getter for object matrix
	virtual void SetIdentity(glm::mat4 identity) { m_identityMat = identity; }
	virtual glm::mat4 GetIdentity() { return m_identityMat; }

	//Setter and getter for object type
	virtual void SetType(ObjectType type) { m_objType = type; }
	virtual ObjectType GetType() { return m_objType; }

	//Function that handle object translation and rotation
	virtual void TranslateObject(glm::vec3 translation);
	virtual void RotateObject(float angle, glm::vec3 rotAxis);

protected:
	
	//object position and orientation storage vectors
	glm::vec3 m_objPos = glm::vec3(0.0f);
	glm::vec3 m_objOrt = glm::vec3(0.0f);
	//Object mtrix storage variable
	glm::mat4 m_identityMat = glm::mat4(0.0f);
	//Object type storage variable
	ObjectType m_objType;
};

