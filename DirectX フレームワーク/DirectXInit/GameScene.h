#pragma once
#include "Scene.h"

class GameScene 
	: public Scene
{
private:
	Quad bg;	//�w�i�I�u�W�F�N�g
public:
	GameScene();	//�R���X�g���N�^(�����������֐�)
	~GameScene();	//�f�X�g���N�^�@(��������֐�)

	//�I�[�o�[���C�h�����֐�
	void Update();	// �X�V�����֐�
	void Draw();	// �`�揈���֐�
	void Uninit();	// ��������֐�
};