#pragma once
#include "GameObject.h"

#include <iostream>

class SceneObject : public GameObject
{
public:
	//Scene object constructor and its various overloaded versions
	SceneObject();
	SceneObject(const char* filePath, ObjectType type);
	SceneObject(glm::vec3 position, glm::vec3 ort, glm::vec3 scale, float angle, glm::vec3 rotAxis, const char* filePath, ObjectType type);
	//Scene object destructor
	~SceneObject();

	//Get model function
	WfModel GetModel() { return m_objModel; }
	//Get model texture ID function
	GLuint GetModelTexId() { return m_objModel.textureId; }

	//Get model vertex array object ID function
	GLuint GetModelVaoId() { return m_objModel.vaoId; }
	//Get model vertex count function
	GLuint GetModelVertexCount() { return m_objModel.vertexCount; }
protected:
	//Modle storage object
	WfModel m_objModel;
};

