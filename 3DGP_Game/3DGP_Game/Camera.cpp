#include "Camera.h"
Camera::Camera()
{
	//Create new perspective matrix to act as a camera
	m_identityMat = glm::perspective(glm::radians(45.0f), (float)600 / (float)600, 0.1f, 100.f);
	//Set camera position and orientation to be 0 by default
	m_objPos = glm::vec3(0.0f);
	m_objOrt = glm::vec3(0.0f);
}

Camera::Camera(glm::vec3 position, glm::vec3 ort, float angle, glm::vec3 rotAxis)
{
	//Create new perspective matrix to act as a camera
	m_identityMat = glm::perspective(glm::radians(45.0f), (float)600 / (float)600, 0.1f, 100.f);
	//Set camera position and orientation to passed in values
	m_objPos = position;
	m_objOrt = ort;
	////Translate and rotate the camera in accordance with the passed in variables to ensure camera is created in the correct position
	m_identityMat = glm::translate(m_identityMat, position);
	m_identityMat = glm::rotate(m_identityMat, glm::radians(angle), rotAxis);
}

Camera::~Camera()
{

}

