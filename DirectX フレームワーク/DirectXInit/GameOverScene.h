#pragma once
#include "Scene.h"
#include "Enum.h"

class GameOverScene 
	: public Scene
{
private:
	//Quad bg;	// �w�i�I�u�W�F�N�g
	//std::vector <std::unique_ptr<Object>>objects;	// �I�u�W�F�N�g�z��
	int frameNum = 1;
public:

	static SCENE isEndSceneNum;

	GameOverScene();		// �R���X�g���N�^(����������)
	~GameOverScene();		// �f�X�g���N�^	(�������)

	//�I�[�o�[���C�h�����֐�
	void Init();		// ����������
	void Update();		// �X�V����
	//void Draw();		// �`�揈��
};