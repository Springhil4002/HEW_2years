#pragma once
#include "Scene.h"

class HomeScene
	: public Scene
{
private:
	int homeSceneNum = 0;	// HomeScene�̐؂�ւ��p�̔ԍ�
	int frameNum = 0;		// frame�̎��ʗp�ԍ�
public:
	bool fadeOut_Start = false;		// �t�F�[�h�J�n�t���O
	bool fadeOut_End = false;		// �t�F�[�h�I���t���O

	HomeScene(int _num);	// �R���X�g���N�^(����������)
	~HomeScene() {};		// �f�X�g���N�^	(�������)

	void Init(int _num);	// ��{�I�ɏ����������͂������g��

	//�I�[�o�[���C�h�����֐�
	void Init() {};			// ����������
	void Update();			// �X�V����

	void Frame_Input();		// �t���[���ړ����͏���
	void Frame_Move();		// �t���[���ړ�����
	void ChangeHome();		// HomwScene�؂�ւ�����
	void Fade_In();			// �t�F�[�h�C������		(���邭�Ȃ�)
	void Fade_Out();		// �t�F�[�h�A�E�g����	(�Â��Ȃ�)

	// �Q�b�^�[�E�Z�b�^�[
	int GetFrameNum() { return frameNum; }
	void SetFrameNum(int _frameNum) { frameNum = _frameNum; }

	int GetHomeSceneNum() { return homeSceneNum; }
	void SetHomeSceneNum(int _homeSceneNum) { homeSceneNum = _homeSceneNum; }
};