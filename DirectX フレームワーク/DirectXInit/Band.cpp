#include "Band.h"

void Band::Init()
{
	// 先端の初期設定
	tip->SetTex("asset/Texture/ground.png");
	tip->SetPos(m_Position.x - 60, m_Position.y, 0);
	tip->SetScale(10, 10, 0);
}

void Band::Update()
{
	// 位置の調整
	m_Position.x = tip->GetPosX() + 60;
}