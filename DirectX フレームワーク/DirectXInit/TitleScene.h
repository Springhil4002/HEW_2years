#pragma once
#include "Scene.h"

class TitleScene 
	: public Scene
{
private:
	int frameNum = 1;				// frame�̎��ʗp�ԍ�
public:
	bool fadeOut_Start = false;		// �t�F�[�h�J�n�t���O
	bool fadeOut_End = false;		// �t�F�[�h�I���t���O

	TitleScene() {};				// �R���X�g���N�^(����������)
	~TitleScene() {};				// �f�X�g���N�^	(�������)

	//�I�[�o�[���C�h�����֐�
	void Init();					// ����������
	void Update();					// �X�V����

	void Frame_Input();				// �t���[���ړ����͏���
	void Frame_Move();				// �t���[���ړ�����
	void Fade_In();					// �t�F�[�h�C������		(���邭�Ȃ�)
	void Fade_Out();				// �t�F�[�h�A�E�g����	(�Â��Ȃ�)

	// �Q�b�^�[�E�Z�b�^�[
	int GetFrameNum() { return frameNum; }
	void SetFrameNum(int _frameNum) { frameNum = _frameNum; }
};