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
	ResultScene(int _num) { Init(_num); };		//�R���X�g���N�^(�����������֐�)
	~ResultScene() {};		//�f�X�g���N�^�@(��������֐�)

	void Init(int _num);

	//�I�[�o�[���C�h�����֐�
	void Init() {}			// ����������
	void Update();			// �X�V�����֐�
};

