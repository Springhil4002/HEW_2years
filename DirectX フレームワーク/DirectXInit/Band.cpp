#include "Band.h"

void Band::Init()
{
	// ��[�̏����ݒ�
	tip->SetTex("asset/Texture/ground.png");
	tip->SetPos(m_Position.x - 60, m_Position.y, 0);
	tip->SetScale(10, 10, 0);
}

void Band::Update()
{
	// �ʒu�̒���
	m_Position.x = tip->GetPosX() + 60;
}