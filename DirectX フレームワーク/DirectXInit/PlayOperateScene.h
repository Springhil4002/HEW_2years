#pragma once
#include "Scene.h"

class PlayOperateScene
	: public Scene
{
private:

public:
	PlayOperateScene();		// �R���X�g���N�^(����������)
	~PlayOperateScene();		// �f�X�g���N�^	(�������)

	//�I�[�o�[���C�h�����֐�
	void Init();
	void Update();		// �X�V����
};