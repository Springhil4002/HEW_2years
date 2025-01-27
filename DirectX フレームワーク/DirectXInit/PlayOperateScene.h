#pragma once
#include "Scene.h"

class PlayOperateScene
	: public Scene
{
private:
	// ���ɂȂ�
public:
	bool fadeOut_Start = false;		// �t�F�[�h�J�n�t���O
	bool fadeOut_End = false;		// �t�F�[�h�I���t���O

	PlayOperateScene() {};			// �R���X�g���N�^(����������)
	~PlayOperateScene() {};			// �f�X�g���N�^	(�������)

	void Back_ToTitle();			// �^�C�g���ɖ߂�
	void Fade_In();					// �t�F�[�h�C������		(���邭�Ȃ�)
	void Fade_Out();				// �t�F�[�h�A�E�g����	(�Â��Ȃ�)

	//�I�[�o�[���C�h�����֐�
	void Init();					// ����������
	void Update();					// �X�V����
};