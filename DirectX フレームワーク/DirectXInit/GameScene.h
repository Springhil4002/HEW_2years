#pragma once
#include "Scene.h"

#define OBJECT_X_VALUE (32)
#define OBJECT_Y_VALUE (18)
#define GROUND_OFFSET_X (-930.0f)
#define GROUND_OFFSET_Y (-510.0f)

class GameScene : public Scene
{
private:
	//Quad bg;		//�w�i�I�u�W�F�N�g
	//Player player;	// �v���C���[
	//std::vector<Ground*> ground;	// �n��
	//Physic test;
public:
	GameScene() {}	//�R���X�g���N�^
	~GameScene();	//�f�X�g���N�^

	//�I�[�o�[���C�h�����֐�
	void Init();
	void Update();	// �X�V�����֐�
	//void Draw();	// �`�揈���֐�
};