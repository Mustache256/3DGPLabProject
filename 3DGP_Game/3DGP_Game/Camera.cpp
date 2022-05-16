#include "Camera.h"
Camera::Camera()
{
	m_identity = glm::perspective(glm::radians(45.0f), (float)600 / (float)600, 0.1f, 100.f);
	m_position = glm::vec3(0.0f);
	m_orientation = glm::vec3(0.0f);
}

Camera::Camera(glm::vec3 position, glm::vec3 ort, float angle, glm::vec3 rotAxis)
{
	m_identity = glm::perspective(glm::radians(45.0f), (float)600 / (float)600, 0.1f, 100.f);
	m_position = position;
	m_orientation = ort;
	m_identity = glm::translate(m_identity, position);
	m_identity = glm::rotate(m_identity, glm::radians(angle), rotAxis);
}

Camera::~Camera()
{

}

