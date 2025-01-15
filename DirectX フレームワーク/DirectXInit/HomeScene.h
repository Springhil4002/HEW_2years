#pragma once
#include "Scene.h"

class HomeScene
	: public Scene
{
private:
	int homeSceneNum = 0;	// HomeScene�̐؂�ւ��p�̔ԍ�
	int frameNum = 0;		// frame�̎��ʗp�ԍ�
public:
	HomeScene(int _num);	// �R���X�g���N�^(����������)
	~HomeScene() {};		// �f�X�g���N�^	(�������)

	void Init(int _num);	// ��{�I�ɏ����������͂������g��

	//�I�[�o�[���C�h�����֐�
	void Init() {};			// ����������
	void Update();			// �X�V����

	void Frame_Input();		// �t���[���ړ����͏���
	void Frame_Move();		// �t���[���ړ�����
	void ChangeHome();		// HomwScene�؂�ւ�����

	// �Q�b�^�[�E�Z�b�^�[
	int GetFrameNum() { return frameNum; }
	void SetFrameNum(int _frameNum) { frameNum = _frameNum; }

	int GetHomeSceneNum() { return homeSceneNum; }
	void SetHomeSceneNum(int _homeSceneNum) { homeSceneNum = _homeSceneNum; }
};