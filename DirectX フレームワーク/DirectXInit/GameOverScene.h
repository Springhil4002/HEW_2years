#pragma once
#include "Scene.h"
#include "Enum.h"

class GameOverScene 
	: public Scene
{
private:
	int frameNum = 1;				// frame�̎��ʗp�ԍ�
public:
	static SCENE isEndSceneNum;		// �Ō�ɏI�����GameScene������ϐ�

	GameOverScene() {};				// �R���X�g���N�^(����������)
	~GameOverScene() {};			// �f�X�g���N�^	(�������)

	//�I�[�o�[���C�h�����֐�
	void Init();					// ����������
	void Update();					// �X�V����
};