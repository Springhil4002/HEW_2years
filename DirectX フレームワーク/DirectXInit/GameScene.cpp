#include "GameScene.h"
#include "SceneManager.h"

GameScene::GameScene()
{
	bg.Init("asset/Texture/Beach.png");	// �w�i��������
	bg.SetScale(1280.0f, 720.0f, 0.0f);	// �傫����ݒ�

	ground.resize(OBJECT_VALUE);
	for (int i = 0; i < OBJECT_VALUE; ++i)
	{
		ground[i] = new Ground;
		ground[i]->Init();	// �n�ʂ�`��
		ground[i]->SetPos(-620 + i * 50, -250.0f, 0.0f);	// ���W��������
	}
}

GameScene::~GameScene()
{
	bg.Uninit();	//�w�i���I��
	for (int i = 0; i < OBJECT_VALUE; ++i)
	{
		ground[i]->Uninit();
	}
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
	bg.Draw();		// �w�i��`��
	for (int i = 0; i < OBJECT_VALUE; ++i)
	{
		ground[i]->Draw();
	}
}
