#include "StarTip.h"

bool StarTip::geting = false;		// starTip�̊l���t���O
bool StarTip::seting = false;		// starTip�̃e�N�X�`���Z�b�g�t���O

void StarTip::Init()
{
	SetTex("asset/Texture/Band_StarTip_Clear.png");		// �摜�ǂݍ���
	SetScale(BLOCK_SIZE*2, BLOCK_SIZE*2, 0.0f);			// �傫����ݒ�
}

void StarTip::Update()
{
	Quad::Update();

	if (geting == true && seting==false) {
		SetTex("asset/Texture/Band_StarTip.png");		// �摜�ǂݍ���
		seting = false;
	}
}
