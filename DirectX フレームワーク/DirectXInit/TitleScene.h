#pragma once
#include "Scene.h"

class TitleScene 
	: public Scene
{
private:
	//Quad bg;	// �w�i�I�u�W�F�N�g
	//std::vector <std::unique_ptr<Object>>objects;	// �I�u�W�F�N�g�z��
	int frameNum = 1;
public:
	TitleScene();		// �R���X�g���N�^(����������)
	~TitleScene();		// �f�X�g���N�^	(�������)

	//�I�[�o�[���C�h�����֐�
	void Init();
	void Update();		// �X�V����
	//void Draw();		// �`�揈��
};