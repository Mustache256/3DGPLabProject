#pragma once
#include "SceneObject.h"

class Enemy : public SceneObject
{
public:
	
	Enemy();
	Enemy(float radius);
	Enemy(float radius, SceneObject* obj);
	~Enemy();

	void EnemyUpdate();
	void AddToEnemyVector(SceneObject* obj) { m_enemies.push_back(obj); }

private:

	std::vector<SceneObject*> m_enemies;
	float m_radius;
};

