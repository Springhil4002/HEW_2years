#include "GameScene.h"
#include "SceneManager.h"
#include "Quad.h"
#include "Ground.h"
#include "Player.h"
#include "Band.h"
#include "Coin.h"
//GameScene::GameScene()
//{
//	bg.Init("asset/Texture/Beach.png");	// 背景を初期化
//	bg.SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);	// 大きさを設定
//
//
//	player.Init("asset/Texture/player.png");// プレイヤーを初期化
//	player.SetPos(playerX, playerY, 0.0f);	// 座標を設定
//	player.SetScale(BLOCK_SIZE, 2*BLOCK_SIZE, 0.0f);	// 大きさを設定
//
//	ground.resize(OBJECT_X_VALUE);
//	for (int i = 0; i < OBJECT_X_VALUE; ++i)
//	{
//		ground[i] = new Ground;
//		ground[i]->Init();	// 地面を描画
//		ground[i]->SetPos(GROUND_OFFSET_X + i * BLOCK_SIZE, GROUND_OFFSET_Y, 0.0f);	// 座標を初期化
//	}
//
//	test.Init("asset/Texture/player.png");
//	test.SetPos(playerX, playerY, 0.0f);	// 座標を設定
//	test.SetScale(BLOCK_SIZE, 2 * BLOCK_SIZE, 0.0f);	// 大きさを設定
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
//	Object::GetObj<Entity>()[0]->SetPos(playerX, playerY, 0.0f);	// 座標を設定
//	Object::GetObj<Entity>()[0]->SetVelo(1, 0, 0);	// を設定
//	Object::GetObj<Entity>()[1]->SetPos(playerX + 120, playerY, 0.0f);	// 座標を設定
//
//
//
//}

GameScene::~GameScene()
{
	//bg.Uninit();		// 背景を終了
	//player.Uninit();	// プレイヤーを終了
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
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// サウンドを停止
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM002);	// サウンドを再生

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
				ground->SetPos(GROUND_OFFSET_X + i * BLOCK_SIZE, -(GROUND_OFFSET_Y + j * BLOCK_SIZE), 0.0f);	// 座標を初期化

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
	
	//input.Update();	//キー入力の判定

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
	
	// "3"キーを押したら
	if (input.GetKeyTrigger(VK_3))
	{
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
		//現在のシーンを「ResultScene」に切り替える
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
//	bg.Draw();		// 背景を描画
//	player.Draw();	// プレイヤーを描画
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
