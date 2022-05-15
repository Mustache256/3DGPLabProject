#include "SceneObject.h"

SceneObject::SceneObject(const char* filePath)
{
	m_position = glm::vec3(0.0f);
	m_orientation = glm::vec3(0.0f);
	m_identity = glm::mat4(1.0f);

	m_model = { 0 };
	if (WfModelLoad(filePath, &m_model))
	{
		throw std::runtime_error("Failed to load model");
	}
}


SceneObject::SceneObject(glm::vec3 position, glm::vec3 ort, float angle, glm::vec3 rotAxis, const char* filePath)
{
	m_position = position;
	m_orientation = ort;
	m_identity = glm::mat4(1.0f);

	m_model = { 0 };
	if (WfModelLoad(filePath, &m_model))
	{
		throw std::runtime_error("Failed to load model");
	}

	m_identity = glm::translate(m_identity, position);
	m_identity = glm::rotate(m_identity, glm::radians(angle), rotAxis);
}

SceneObject::~SceneObject()
{
	WfModelDestroy(&m_model);
}
