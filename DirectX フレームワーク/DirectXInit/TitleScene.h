#pragma once
#include "Scene.h"

class TitleScene 
	: public Scene
{
private:
	TestQuad BackGround;	//�w�i�I�u�W�F�N�g
public:
	TitleScene();		//�R���X�g���N�^(����������)
	~TitleScene();		//�f�X�g���N�^	(�������)

	//�I�[�o�[���C�h�����֐�
	void Update();		//�X�V����
	void Draw();		//�`�揈��
};