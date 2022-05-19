#include "SceneObject.h"

SceneObject::SceneObject()
{

}

SceneObject::SceneObject(const char* filePath, ObjectType type)
{
	//Set object position and orientation vectors to 0 by default
	m_objPos = glm::vec3(0.0f);
	m_objOrt = glm::vec3(0.0f);
	//Create identity matrix
	m_identityMat = glm::mat4(1.0f);

	//Load the correct model and check to see if the model has loaded properly
	m_objModel = { 0 };
	if (WfModelLoad(filePath, &m_objModel))
	{
		throw std::runtime_error("Failed to load model");
	}

	//Set object type 
	m_objType = type;
}

SceneObject::SceneObject(glm::vec3 position, glm::vec3 ort, glm::vec3 scale, float angle, glm::vec3 rotAxis, const char* filePath, ObjectType type)
{
	//Set object position and orientation vectors to associated input vector
	m_objPos = position;
	m_objOrt = ort;
	//Create identity matrix
	m_identityMat = glm::mat4(1.0f);

	//Load the correct model and check to see if the model has loaded properly
	m_objModel = { 0 };
	if (WfModelLoad(filePath, &m_objModel))
	{
		throw std::runtime_error("Failed to load model");
	}

	//Translate, rotate and scale the object in accordance with the passed in variables to ensure object is created in the correct position
	m_identityMat = glm::translate(m_identityMat, position);
	m_identityMat = glm::rotate(m_identityMat, glm::radians(angle), rotAxis);
	m_identityMat = glm::scale(m_identityMat, scale);

	//Set object type 
	m_objType = type;
}

SceneObject::~SceneObject()
{
	//Destroy the loaded model
	WfModelDestroy(&m_objModel);
}
