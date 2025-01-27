#pragma once
#include "Scene.h"
#include "Enum.h"

#define SCENE_ENUM_OFFSET	(3)

class GameOverScene 
	: public Scene
{
private:
	int frameNum = 1;				// frame�̎��ʗp�ԍ�
public:
	static SCENE isEndSceneNum;		// �Ō�ɏI�����GameScene������ϐ�
	bool fadeOut_Start = false;		// �t�F�[�h�J�n�t���O
	bool fadeOut_End = false;		// �t�F�[�h�I���t���O

	GameOverScene() {};				// �R���X�g���N�^(����������)
	~GameOverScene() {};			// �f�X�g���N�^	(�������)

	void Frame_Input();				// �t���[���ړ����͏���
	void Frame_Move();				// �t���[���ړ�����
	void Fade_In();					// �t�F�[�h�C������		(���邭�Ȃ�)
	void Fade_Out();				// �t�F�[�h�A�E�g����	(�Â��Ȃ�)

	//�I�[�o�[���C�h�����֐�
	void Init();					// ����������
	void Update();					// �X�V����

	// �Q�b�^�[�E�Z�b�^�[
	int GetFrameNum() { return frameNum; }
	void SetFrameNum(int _frameNum) { frameNum = _frameNum; }
};