#include "Entity.h"

void Entity::Update()
{
	Physic::Update();

	auto allEntity = Object::GetObj<Entity>();

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