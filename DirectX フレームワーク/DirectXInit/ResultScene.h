#pragma once
#include "Scene.h"

#define SET_STARTIP			(3)
#define SET_BLOCK			(100)

class ResultScene
	: public Scene
{
private:
	static int tipCount;			// bandTip�̊l����
	static int meterCount;			// �����ς����o���h�J�E���g
public:
	bool drawFlag = true;			// CLEAR���S�`��t���O
	bool drawClearFlag = false;		// CLEAR���S�`�抮���t���O	
	bool moveFlag = false;			// CLEAR���S�ړ��t���O
	int count = 0;					// frameCount

	ResultScene(int _num)			//�R���X�g���N�^(�����������֐�)
	{ Init(_num); };		
	~ResultScene() {};				//�f�X�g���N�^�@(��������֐�)

	void Init(int _num);			// ��{�I�Ɏg������������

	//�I�[�o�[���C�h�����֐�
	void Init() {}					// ����������
	void Update();					// �X�V�����֐�

	void PullScoreUpdate();			// ���������������ɉ����ăX�R�A���X�V
	void CoinCounter();				// �R�C���l����UI�̊e���X�V����
	void CoinGetPercent();			// �R�C���l�����̊����ɉ�����StarTip�̊l���󋵂̍X�V
	void ClearBig();				// CLEAR�̃��S�g��\��
	void ClearMove();				// CLEAR�̃��S�k���ړ�
	void ClearDraw();				// CLEAR���S�̕`�揈��
};

