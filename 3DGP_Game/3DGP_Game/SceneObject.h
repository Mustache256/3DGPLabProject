#pragma once
#include "GameObject.h"

#include <iostream>

class SceneObject : public GameObject
{
public:
	SceneObject();
	SceneObject(const char* filePath, ObjectType type);
	SceneObject(glm::vec3 position, glm::vec3 ort, glm::vec3 scale, float angle, glm::vec3 rotAxis, const char* filePath, ObjectType type);
	~SceneObject();

	WfModel GetModel() { return m_model; }
	GLuint GetModelTexId() { return m_model.textureId; }
	GLuint GetModelVaoId() { return m_model.vaoId; }
	GLuint GetModelVertexCount() { return m_model.vertexCount; }
protected:

	WfModel m_model;
};

