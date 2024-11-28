#include "Object.h"

Shader Object::m_Shader;

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

void Object::CreateShader()
{
	m_Shader.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");
}