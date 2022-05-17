#pragma once
#include "SceneObject.h"

class Enemy : public SceneObject
{
public:
	
	Enemy();
	~Enemy();

	void enemyUpdate();

private:
	std::vector<SceneObject*> m_enemies;
	float m_radius;
};

