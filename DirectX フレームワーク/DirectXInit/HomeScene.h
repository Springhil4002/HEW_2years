#pragma once
#include "Scene.h"

class HomeScene
	: public Scene
{
private:
	//Quad bg;	// �w�i�I�u�W�F�N�g
	//std::vector <std::unique_ptr<Object>>objects;	// �I�u�W�F�N�g�z��
	int homeSceneNum = 0;	// HomeScene�̐؂�ւ��p�̔ԍ�
	int frameNum = 0;		// frame�̎��ʗp�ԍ�
public:
	HomeScene(int _num);		// �R���X�g���N�^(����������)
	~HomeScene();		// �f�X�g���N�^	(�������)

	//�I�[�o�[���C�h�����֐�
	void Init() {};
	void Init(int _num);
	void Update();		// �X�V����
	//void Draw();		// �`�揈��
};