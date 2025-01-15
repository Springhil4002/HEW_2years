#pragma once
#include "Scene.h"

class TitleScene 
	: public Scene
{
private:
	int frameNum = 1;		// frame�̎��ʗp�ԍ�
public:
	TitleScene() {};		// �R���X�g���N�^(����������)
	~TitleScene() {};		// �f�X�g���N�^	(�������)

	//�I�[�o�[���C�h�����֐�
	void Init();			// ����������
	void Update();			// �X�V����

	void Frame_Input();		// �t���[���ړ����͏���
	void Frame_Move();		// �t���[���ړ�����

	// �Q�b�^�[�E�Z�b�^�[
	int GetFrameNum() { return frameNum; }
	void SetFrameNum(int _frameNum) { frameNum = _frameNum; }
};