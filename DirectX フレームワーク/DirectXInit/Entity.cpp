#include "Entity.h"

void Entity::Update()
{	
	m_Velocity += m_Acceleration;

	if (m_Velocity.LengthSquared() > 0.0001f)
	{
		auto buf = m_Position;
		auto allEntity = Scene::GetInstance()->GetObjects<Entity>();

		m_Position.x += m_Velocity.x;
		bool coll = false;
		for (auto& sub : allEntity)
		{
			while (Object::Collision(this, sub))
			{
				m_Position.x -= m_Velocity.x / 10;
			}
		}

		m_Position.y += m_Velocity.y;
		for (auto& sub : allEntity)
		{
			while (Object::Collision(this, sub))
			{
				m_Position.y -= m_Velocity.y / 10;
			}
		}

		m_Velocity = m_Position - buf;
	}
	else
	{
		m_Velocity = DirectX::SimpleMath::Vector3(0, 0, 0);
	}


	Quad::Update();
}