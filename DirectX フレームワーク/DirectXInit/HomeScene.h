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
};