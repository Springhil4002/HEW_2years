#pragma once
#include "Scene.h"

#define OBJECT_VALUE (26)

class GameScene 
	: public Scene
{
private:
	Quad bg;	//�w�i�I�u�W�F�N�g
	std::vector<Ground*> ground;	// �n��
public:
	GameScene();	//�R���X�g���N�^(�����������֐�)
	~GameScene();	//�f�X�g���N�^�@(��������֐�)

	//�I�[�o�[���C�h�����֐�
	void Update();	// �X�V�����֐�
	void Draw();	// �`�揈���֐�
};