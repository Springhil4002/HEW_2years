#include "Entity.h"

void Entity::Update()
{
	Physic::Update();

	auto allEntity = Scene::GetInstance()->GetObjects<Entity>();

	for (auto& main : allEntity)
	{
		for (auto& sub : allEntity)
		{
			if (Object::Collision(main, sub))
			{
				main->m_Velocity = { 0,0,0 };
			}
		}
	}
}