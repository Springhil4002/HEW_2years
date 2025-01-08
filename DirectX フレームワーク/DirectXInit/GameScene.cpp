#include "GameScene.h"
#include "SceneManager.h"
#include "Quad.h"
#include "Ground.h"
#include "Player.h"
#include "Band.h"
#include "Coin.h"
//GameScene::GameScene()
//{
//	bg.Init("asset/Texture/Beach.png");	// �w�i��������
//	bg.SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);	// �傫����ݒ�
//
//
//	player.Init("asset/Texture/player.png");// �v���C���[��������
//	player.SetPos(playerX, playerY, 0.0f);	// ���W��ݒ�
//	player.SetScale(BLOCK_SIZE, 2*BLOCK_SIZE, 0.0f);	// �傫����ݒ�
//
//	ground.resize(OBJECT_X_VALUE);
//	for (int i = 0; i < OBJECT_X_VALUE; ++i)
//	{
//		ground[i] = new Ground;
//		ground[i]->Init();	// �n�ʂ�`��
//		ground[i]->SetPos(GROUND_OFFSET_X + i * BLOCK_SIZE, GROUND_OFFSET_Y, 0.0f);	// ���W��������
//	}
//
//	test.Init("asset/Texture/player.png");
//	test.SetPos(playerX, playerY, 0.0f);	// ���W��ݒ�
//	test.SetScale(BLOCK_SIZE, 2 * BLOCK_SIZE, 0.0f);	// �傫����ݒ�
//	test.SetAcce(0, -1, 0);
//	test.SetVelo(1, 20, 0);
//
//
//	Object* buf[2];
//	buf[0] = new Entity;
//	buf[1] = new Entity;
//	Object::GetInstance()->push_back(buf[0]);
//	Object::GetInstance()->push_back(buf[1]);
//	for (auto& ent : Object::GetObj<Entity>())
//	{
//		ent->Init("asset/Texture/explotion.png");
//		ent->SetScale(60, 60, 0);
//	}
//	Object::GetObj<Entity>()[0]->SetPos(playerX, playerY, 0.0f);	// ���W��ݒ�
//	Object::GetObj<Entity>()[0]->SetVelo(1, 0, 0);	// ��ݒ�
//	Object::GetObj<Entity>()[1]->SetPos(playerX + 120, playerY, 0.0f);	// ���W��ݒ�
//
//
//
//}

GameScene::~GameScene()
{
	//bg.Uninit();		// �w�i���I��
	//player.Uninit();	// �v���C���[���I��
	//for (int i = 0; i < OBJECT_X_VALUE; ++i)
	//{
	//	ground[i]->Uninit();
	//}
	//test.Uninit();
	//for (auto& ent : Object::GetObj<Entity>())
	//{
	//	ent->Uninit();
	//}
}

void GameScene::Init()
{	
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// �T�E���h���~
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM002);	// �T�E���h���Đ�

	auto bg = Object::Create<Quad>();
	bg->SetTex("asset/Texture/Beach.png");
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
	bg->layer = -1;

	const int stage[OBJECT_Y_VALUE][OBJECT_X_VALUE] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1}
	};


	for (int i = 0; i < OBJECT_X_VALUE; i++)
	{
		for (int j = 0; j < OBJECT_Y_VALUE; j++)
		{
			switch (stage[j][i])
			{
			case 1:
				auto ground = Object::Create<Ground>();
				ground->SetPos(GROUND_OFFSET_X + i * BLOCK_SIZE, -(GROUND_OFFSET_Y + j * BLOCK_SIZE), 0.0f);	// ���W��������

				if (20 <= i && i <= 25)
				{
					ground->tags.AddTag("BandA");
				}
				break;
			}
		}
	}

	auto player = Object::Create<Player>();
	player->layer = 1;

	auto band = Object::Create<Band>();
	band->SetTex("asset/Texture/ground.png");
	band->SetPos(30, -422, 0);
	band->SetScale(60, 60, 0);
	for (auto& obj : objectInstance)
	{
		if (obj->tags.SearchTag("BandA"))
		{
			band->Add(obj);
		}
	}


	auto check = Object::Create<Quad>();
	check->SetTex("asset/Texture/explotion.png");
	check->SetScale(100, 100, 0);
	check->tags.AddTag("check");


	auto coin = Object::Create<Coin>();


	for (auto& obj : objectInstance)
	{
		obj->Init();
	}
}

void GameScene::Update()
{
	
	//input.Update();	//�L�[���͂̔���

	//player.Update();

	//test.Update();

	/*for (auto& ent : Object::GetObj<Entity>())
	{
		ent->Update();
	}*/

	auto objects = objectInstance;
	for (auto& obj : objects)
	{
		obj->Update();
	}
	
	// "3"�L�[����������
	if (input.GetKeyTrigger(VK_3))
	{
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
		//���݂̃V�[�����uResultScene�v�ɐ؂�ւ���
		SceneManager::ChangeScene(SceneManager::RESULT);
	}

	auto players =GetInstance()->GetObjects<Player>();
	for (auto& player : players)
	{
		if (GROUND_OFFSET_Y > player->GetPos().y + 120.0f)
		{
			SceneManager::ChangeScene(SceneManager::GAMEOVER);
		}
	}
}

//void GameScene::Draw()
//{
//	bg.Draw();		// �w�i��`��
//	player.Draw();	// �v���C���[��`��
//	for (int i = 0; i < OBJECT_X_VALUE; ++i)
//	{
//		ground[i]->Draw();
//	}
//	test.Draw();
//
//	for (auto& ent : Object::GetObj<Entity>())
//	{
//		ent->Draw();
//	}
//}
