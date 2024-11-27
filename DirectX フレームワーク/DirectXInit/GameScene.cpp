#include "GameScene.h"
#include "SceneManager.h"

GameScene::GameScene()
{
	bg.Init("asset/Texture/Beach.png");	// �w�i��������
	bg.SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);	// �傫����ݒ�

	const float playerX = GROUND_OFFSET_X + 20.0f;
	const float playerY = GROUND_OFFSET_Y + (2 * BLOCK_SIZE);

	player.Init("asset/Texture/player.png");// �v���C���[��������
	player.SetPos(playerX, playerY, 0.0f);	// ���W��ݒ�
	player.SetScale(BLOCK_SIZE, 2*BLOCK_SIZE, 0.0f);	// �傫����ݒ�

	ground.resize(OBJECT_X_VALUE);
	for (int i = 0; i < OBJECT_X_VALUE; ++i)
	{
		ground[i] = new Ground;
		ground[i]->Init();	// �n�ʂ�`��
		ground[i]->SetPos(GROUND_OFFSET_X + i * BLOCK_SIZE, GROUND_OFFSET_Y, 0.0f);	// ���W��������
	}
}

GameScene::~GameScene()
{
	bg.Uninit();		// �w�i���I��
	player.Uninit();	// �v���C���[���I��
	for (int i = 0; i < OBJECT_X_VALUE; ++i)
	{
		ground[i]->Uninit();
	}
}

void GameScene::Update()
{
	input.Update();	//�L�[���͂̔���

	player.Update();

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
	player.Draw();	// �v���C���[��`��
	for (int i = 0; i < OBJECT_X_VALUE; ++i)
	{
		ground[i]->Draw();
	}
}
