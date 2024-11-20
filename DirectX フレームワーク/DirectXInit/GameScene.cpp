#include "GameScene.h"
#include "SceneManager.h"

GameScene::GameScene()
{
	bg.Init("asset/Texture/Beach.png");			//�w�i��������
	bg.SetScale(1280.0f, 720.0f, 0.0f);	//�傫����ݒ�
}

GameScene::~GameScene()
{
	bg.Uninit();	//�w�i���I��
}

void GameScene::Update()
{
	input.Update();	//�L�[���͂̔���

	// "1"�L�[����������
	if (input.GetKeyTrigger(VK_1))
	{
		//���݂̃V�[�����uResultScene�v�ɐ؂�ւ���
		SceneManager::ChangeScene(SceneManager::TITLE);
	}

	// "3"�L�[����������
	if (input.GetKeyTrigger(VK_3))
	{
		//���݂̃V�[�����uResultScene�v�ɐ؂�ւ���
		SceneManager::ChangeScene(SceneManager::RESULT);
	}
}

void GameScene::Draw()
{
	bg.Draw();		//�w�i��`��
}
