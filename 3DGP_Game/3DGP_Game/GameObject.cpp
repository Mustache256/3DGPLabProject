#include "GameObject.h"


void GameObject::TranslateObject(glm::vec3 translation)
{
	//Translate the object through the use of its identity matrix and update its position vector accordingly
	m_identityMat = glm::translate(m_identityMat, translation);
	m_objPos += translation;
}

void GameObject::RotateObject(float angle, glm::vec3 rotAxis)
{
	//Rotate the object through the use of its identity matrix
	m_identityMat = glm::rotate(m_identityMat, glm::radians(angle), rotAxis);
}