#pragma once
#include "Scene.h"
#include "Enum.h"

class GameOverScene 
	: public Scene
{
private:
	int frameNum = 1;				// frame�̎��ʗp�ԍ�
public:
	static SCENE isEndSceneNum;		// �Ō�ɏI�����GameScene������ϐ�

	GameOverScene() {};				// �R���X�g���N�^(����������)
	~GameOverScene() {};			// �f�X�g���N�^	(�������)

	void Frame_Input();				// �t���[���ړ����͏���
	void Frame_Move();				// �t���[���ړ�����

	//�I�[�o�[���C�h�����֐�
	void Init();					// ����������
	void Update();					// �X�V����

	// �Q�b�^�[�E�Z�b�^�[
	int GetFrameNum() { return frameNum; }
	void SetFrameNum(int _frameNum) { frameNum = _frameNum; }
};