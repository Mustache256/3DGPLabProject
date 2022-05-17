#include "Enemy.h"

Enemy::Enemy()
{
	m_radius = 1.0f;
}

Enemy::Enemy(float radius)
{
	m_radius = radius;
}

Enemy::Enemy(float radius, SceneObject* obj)
{
	m_radius = radius;
	m_enemies.push_back(obj);
}

Enemy::~Enemy()
{

}

void Enemy::EnemyUpdate()
{
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies.at(i)->TranslateObject(glm::vec3(1.0f, 0.0f, 0.0f));

	}
}
