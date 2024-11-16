#include "GameScene.h"
#include "SceneManager.h"

GameScene::GameScene()
{
	BackGround.Init("asset/Texture/Beach.png");			//�w�i��������
	BackGround.SetScale(1280.0f, 720.0f, 0.0f);	//�傫����ݒ�
}

GameScene::~GameScene()
{
	BackGround.Uninit();	//�w�i���I��
}

void GameScene::Update()
{
	input.Update();	//�L�[���͂̔���
	//�G���^�[�L�[����������
	if (input.GetKeyTrigger(VK_3))
	{
		//���݂̃V�[�����uResultScene�v�ɐ؂�ւ���
		SceneManager::ChangeScene(SceneManager::RESULT);
	}
}

void GameScene::Draw()
{
	BackGround.Draw();		//�w�i��`��
}


