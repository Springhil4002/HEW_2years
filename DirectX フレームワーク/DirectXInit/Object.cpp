#include "Object.h"

Shader Object::m_Shader;

// 今のとこ追記なし
void Object::SetPos(float _x, float _y, float _z)
{
	//座標をセットする
	m_Position.x = _x;
	m_Position.y = _y;
	m_Position.z = _z;
}
void Object::SetScale(float _x, float _y, float _z)
{
	//大きさをセットする
	m_Scale.x = _x;
	m_Scale.y = _y;
	m_Scale.z = _z;
}
void Object::SetRotation(float _x, float _y, float _z)
{
	// 角度をセットする
	m_Rotation.x = _x;
	m_Rotation.y = _y;
	m_Rotation.z = _z;
}

bool Object::SearchTag(const std::string _tag) const
{
	// タグを検索して返す
	return tags.SearchTag(_tag);
}

void Object::CreateShader()
{
	m_Shader.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");
}