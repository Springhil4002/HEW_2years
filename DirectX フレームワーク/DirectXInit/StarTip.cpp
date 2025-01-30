#include "StarTip.h"

void StarTip::Init()
{
	SetTex("asset/Texture/Band_StarTip_Clear.png");		// �摜�ǂݍ���
	SetScale(BLOCK_SIZE*6, BLOCK_SIZE*6, 0.0f);			// �傫����ݒ�
	layer = 1;											// ���C���[��ݒ�
}

void StarTip::Update()
{
	Quad::Update();

	if (geting == true && seting == false) {
		SetTex("asset/Texture/Band_StarTip.png");		// �摜�ǂݍ���
		SetScale(BLOCK_SIZE * 4, BLOCK_SIZE * 4, 0.0f);	// �傫����ݒ�
		seting = true;
	}
}
