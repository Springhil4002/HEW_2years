#pragma once
#include "Scene.h"

#define OBJECT_X_VALUE		(64)
#define OBJECT_Y_VALUE		(18)
#define GROUND_OFFSET_X		(-1890.0f)
#define GROUND_OFFSET_Y		(-510.0f)

class ResultScene
	: public Scene
{
private:
	
public:
	ResultScene() {};		//�R���X�g���N�^(�����������֐�)
	~ResultScene() {};		//�f�X�g���N�^�@(��������֐�)

	//�I�[�o�[���C�h�����֐�
	void Init();			// ����������
	void Update();			// �X�V�����֐�
};

