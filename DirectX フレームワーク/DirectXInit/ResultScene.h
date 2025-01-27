#pragma once
#include "Scene.h"

#define SET_STARTIP			(3)
#define SET_BLOCK			(100)

class GameOverScene;

class ResultScene
	: public Scene
{
private:
	static int tipCount;			// bandTip�̊l����
	static int meterCount;			// �����ς����o���h�J�E���g
	int frameNum = 1;				// frame�̎��ʗp�ԍ�
public:
	bool drawFlag = true;			// CLEAR���S�`��t���O
	bool drawClearFlag = false;		// CLEAR���S�`�抮���t���O	
	bool moveFlag = false;			// CLEAR���S�ړ��t���O
	bool uiFlag = false;			// UI�`��t���O
	bool layerFlag = false;			// UI���C���[�t���O
	bool movePlayerFlag = true;		// playerMove�t���O

	bool fadeOut_Start = false;		// �t�F�[�h�J�n�t���O
	bool fadeOut_End = false;		// �t�F�[�h�I���t���O

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
	void UI_Draw();					// UI�\���`��

	void Frame_Update();			// �t���[���X�V����
	void Frame_Input();				// �t���[���ړ����͏���
	void Frame_Move();				// �t���[���ړ�����

	void Fade_In();					// �t�F�[�h�C������		(���邭�Ȃ�)
	void Fade_Out();				// �t�F�[�h�A�E�g����	(�Â��Ȃ�)

	// �Q�b�^�[�E�Z�b�^�[
	int GetFrameNum() { return frameNum; }
	void SetFrameNum(int _frameNum) { frameNum = _frameNum; }
};

