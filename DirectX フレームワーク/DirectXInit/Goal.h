#pragma once
#include "Quad.h"

class GameScene;
class Goal
	: public Quad
{
public:
	Goal() {}			// �R���X�g���N�^
	~Goal() {}			// �f�X�g���N�^

	// �I�[�o�[���C�h�����֐�
	void Init();		// ����������
	void Update();		// �X�V����
};
