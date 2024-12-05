#include "Object.h"

// ���̂Ƃ��ǋL�Ȃ�
void Object::SetPos(float _x, float _y, float _z)
{
	//���W���Z�b�g����
	m_Position.x = _x;
	m_Position.y = _y;
	m_Position.z = _z;
}
void Object::SetScale(float _x, float _y, float _z)
{
	//�傫�����Z�b�g����
	m_Scale.x = _x;
	m_Scale.y = _y;
	m_Scale.z = _z;
}
void Object::SetRotation(float _x, float _y, float _z)
{
	// �p�x���Z�b�g����
	m_Rotation.x = _x;
	m_Rotation.y = _y;
	m_Rotation.z = _z;
}

bool Object::SearchTag(const std::string _tag) const
{
	// �^�O���������ĕԂ�
	return tags.SearchTag(_tag);
}

void Object::Delete(Object* _object)
{
	auto begin = Scene::GetInstance()->GetObjects()->begin();
	auto end = Scene::GetInstance()->GetObjects()->end();
	for (auto itr = begin; itr != end; itr++)
	{
		if (*itr == _object)
		{
			Scene::GetInstance()->GetObjects()->erase(itr);
			return;
		}
	}
}

bool Object::Collision(Object* _object1, Object* _object2)
{
	// �����ƏՓ˂�����ĉ�����
	if (_object1 == _object2)
	{
		return false;
	}
	else
	{
		// 2�̒��S�����̐�Βl���v�Z
		DirectX::SimpleMath::Vector3 distance;
		distance = _object1->m_Position - _object2->m_Position;
		distance = { abs(distance.x), abs(distance.y), 0 };

		// 2�̕��̍��v���v�Z
		DirectX::SimpleMath::Vector3 sumScale;
		sumScale = _object1->m_Scale + _object2->m_Scale;
		sumScale /= 2;

		// �����������������傫����ΏՓ�
		return distance.x < sumScale.x && distance.y < sumScale.y;
	}
}