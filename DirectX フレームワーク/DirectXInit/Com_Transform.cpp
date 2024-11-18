#include "Com_Transform.h"

// 初期化処理
void Transform::Start()
{

}

// 更新処理
void Transform::Update()
{

}

// 描画処理
void Transform::Draw()
{

}

void Transform::SetPos(float _x, float _y, float _z)
{
	//座標をセットする
	m_Position.x = _x;
	m_Position.y = _y;
	m_Position.z = _z;
}
void Transform::SetScale(float _x, float _y, float _z)
{
	//大きさをセットする
	m_Scale.x = _x;
	m_Scale.y = _y;
	m_Scale.z = _z;
}
void Transform::SetRotation(float _x, float _y, float _z)
{
	// 角度をセットする
	m_Rotation.x = _x;
	m_Rotation.y = _y;
	m_Rotation.z = _z;
}