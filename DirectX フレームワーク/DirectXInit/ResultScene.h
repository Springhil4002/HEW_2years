#pragma once
#include "Scene.h"

class ResultScene
	: public Scene
{
private:
	TestQuad BackGround;	//�w�i�I�u�W�F�N�g
public:
	ResultScene();	//�R���X�g���N�^(�����������֐�)
	~ResultScene();	//�f�X�g���N�^�@(��������֐�)

	//�I�[�o�[���C�h�����֐�
	void Update();	//�X�V�����֐�
	void Draw();	//�`�揈���֐�
};

