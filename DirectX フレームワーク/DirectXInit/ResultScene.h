#pragma once
#include "Scene.h"

#define SET_STARTIP			(3)

class ResultScene
	: public Scene
{
private:
	static int tipCount;		// bandTip�̊l����
	static int meterCount;		// �����ς����o���h�J�E���g
public:
	ResultScene(int _num) { Init(_num); };		//�R���X�g���N�^(�����������֐�)
	~ResultScene() {};							//�f�X�g���N�^�@(��������֐�)

	void Init(int _num);

	//�I�[�o�[���C�h�����֐�
	void Init() {}			// ����������
	void Update();			// �X�V�����֐�
};

