#pragma once
#include "Scene.h"

#define SET_STARTIP			(3)
#define SET_BLOCK			(100)

class ResultScene
	: public Scene
{
private:
	static int tipCount;		// bandTip�̊l����
	static int meterCount;		// �����ς����o���h�J�E���g
public:
	bool flag = false;			// �t���O�ݒ�t���O
	bool Check_Clear = false;	// CLEAR���S�`�抮���t���O
	ResultScene(int _num) { Init(_num); };		//�R���X�g���N�^(�����������֐�)
	~ResultScene() {};							//�f�X�g���N�^�@(��������֐�)

	void Init(int _num);

	//�I�[�o�[���C�h�����֐�
	void Init() {}			// ����������
	void Update();			// �X�V�����֐�

	void PullScoreUpdate();	// ���������������ɉ����ăX�R�A���X�V
	void CoinCounter();		// �R�C���l����UI�̊e���X�V����
	void CoinGetPercent();	// �R�C���l�����̊����ɉ�����StarTip�̊l���󋵂̍X�V
	void ClearDraw();		// CLEAR�̃��S�\�����o
	void ClearMove();		// CLEAR�̃��S�ړ�
};

