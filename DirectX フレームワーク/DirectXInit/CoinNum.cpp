#include "CoinNum.h"

void CoinNum::Init()
{
	SetTex("asset/Texture/Number.png", 10, 1, 0, 0);	// �摜�ǂݍ���
	SetScale(50.0f, 100.0f, 0.0f);						// �傫����ݒ�
}

void CoinNum::Update()
{
	Quad::Update();
}


