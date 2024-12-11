#include "Entity.h"

void Entity::Update()
{	
	// �����x�𑬓x�ɑ���
	m_Velocity += m_Acceleration;

	// ���x��0���傫���Ȃ�
	if (m_Velocity.LengthSquared() > 0.001f)
	{
		// ���̈ʒu�ۑ�
		auto buf = m_Position;
		// �S�Ă�Entity���擾
		auto allEntity = Scene::GetInstance()->GetObjects<Entity>();

		// ���x���ʒu�ɑ���
		m_Position.x += m_Velocity.x;
		// �Փ˃t���O
		bool coll = false;
		// �J�E���^
		int cnt = 0;

		for (auto& sub : allEntity)
		{
			while (Object::Collision(this, sub) && cnt < 8)
			{
				// 8��܂Ŗ߂�
				m_Position.x -= m_Velocity.x / 8;
				cnt++;
			}
		}

		cnt = 0;
		m_Position.y += m_Velocity.y;
		for (auto& sub : allEntity)
		{
			while (Object::Collision(this, sub) && cnt < 8)
			{
				// 8��܂Ŗ߂�
				m_Position.y -= m_Velocity.y / 8;
				cnt++;
			}
		}

		// ���̍��W���瑬�x�Čv�Z
		m_Velocity = m_Position - buf;
	}
	else
	{
		// ���x�����S��0�ɂ���
		m_Velocity = DirectX::SimpleMath::Vector3(0, 0, 0);
	}

	// �`�揈��
	Quad::Update();
}