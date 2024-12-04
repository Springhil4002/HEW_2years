#include "GameScene.h"
#include "SceneManager.h"

GameScene::GameScene()
{
	bg.Init("asset/Texture/Beach.png");	// �w�i��������
	bg.SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);	// �傫����ݒ�

	const float playerX = GROUND_OFFSET_X + 20.0f;
	const float playerY = GROUND_OFFSET_Y + (1.5*BLOCK_SIZE);

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

	test.Init("asset/Texture/player.png");
	test.SetPos(playerX, playerY, 0.0f);	// ���W��ݒ�
	test.SetScale(BLOCK_SIZE, 2 * BLOCK_SIZE, 0.0f);	// �傫����ݒ�
	test.SetAcce(0, -1, 0);
	test.SetVelo(1, 20, 0);


	Object* buf[2];
	buf[0] = new Entity;
	buf[1] = new Entity;
	Object::GetInstance()->push_back(buf[0]);
	Object::GetInstance()->push_back(buf[1]);
	for (auto& ent : Object::GetObj<Entity>())
	{
		ent->Init("asset/Texture/explotion.png");
		ent->SetScale(60, 60, 0);
	}
	Object::GetObj<Entity>()[0]->SetPos(playerX, playerY, 0.0f);	// ���W��ݒ�
	Object::GetObj<Entity>()[0]->SetVelo(1, 0, 0);	// ��ݒ�
	Object::GetObj<Entity>()[1]->SetPos(playerX + 120, playerY, 0.0f);	// ���W��ݒ�



}

GameScene::~GameScene()
{
	bg.Uninit();		// �w�i���I��
	player.Uninit();	// �v���C���[���I��
	for (int i = 0; i < OBJECT_X_VALUE; ++i)
	{
		ground[i]->Uninit();
	}
	test.Uninit();
	for (auto& ent : Object::GetObj<Entity>())
	{
		ent->Uninit();
	}
}

void GameScene::Update()
{
	input.Update();	//�L�[���͂̔���

	player.Update();

	test.Update();

	for (auto& ent : Object::GetObj<Entity>())
	{
		ent->Update();
	}


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
	test.Draw();

	for (auto& ent : Object::GetObj<Entity>())
	{
		ent->Draw();
	}
}
