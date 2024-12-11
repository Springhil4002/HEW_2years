#include "Band.h"

void Band::Init()
{
	// æ’[‚Ì‰ŠúÝ’è
	tip->SetTex("asset/Texture/ground.png");
	tip->SetPos(m_Position.x - 60, m_Position.y, 0);
	tip->SetScale(10, 10, 0);
}

void Band::Update()
{
	// ˆÊ’u‚Ì’²®
	m_Position.x = tip->GetPosX() + 60;
}