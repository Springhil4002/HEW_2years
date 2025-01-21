#include "GameScene.h"
#include "GameOverScene.h"
#include "SceneManager.h"
#include "Quad.h"
#include "Ground.h"
#include "Player.h"
#include "Band.h"
#include "Coin.h"
#include "CoinNum.h"
#include "Goal.h"

//#include "iostream"

int GameScene::bandTipCount = 0;		// bandTipの獲得数

void GameScene::Init(int _num)
{	
	bandTipCount = 0;
	gameSceneNum = _num;
	GameOverScene::isEndSceneNum = (SCENE)(gameSceneNum + SCENE_ENUM_OFFSET);
	switch(gameSceneNum)
	{
	case 1: {
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// サウンドを停止
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// サウンドを停止
		SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// サウンドを再生

		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_1.jpg");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -1;

		const int stage[OBJECT_Y_VALUE][OBJECT_X_VALUE] = {
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1},
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
		band->SetTex("asset/Texture/band_Block.png");
		band->SetPos(30.0f, -420.0f, 0.0f);
		band->SetScale(BLOCK_SIZE, BLOCK_SIZE, 0.0f);
		band->layer = 1;
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
		

		// バンドチップオブジェクトの作成
		Coin* coin[SET_COIN];
		for (int i = 0; i < SET_COIN; i++)
		{
			coin[i] = Object::Create<Coin>();
		}

		
		// バンドチップオブジェクトの座標設定
		for (int i = 0; i < SET_COIN; i++)
		{
			coin[i]->SetPos(BLOCK_SIZE*(-12.5+i), BLOCK_SIZE*-6.5, 0.0f);
		}

		// ゴールオブジェクトの作成
		auto goal = Object::Create<Goal>();
		goal->SetPos(BLOCK_SIZE * 14.5, -BLOCK_SIZE * 7, 0.0f);

		// コイン獲得数オブジェクトの作成
		auto coinNum1	= Object::Create<CoinNum>();
		auto coinNum10	= Object::Create<CoinNum>();
		auto coinNum100 = Object::Create<CoinNum>();
		
		// コイン獲得数オブジェクトの座標設定
		coinNum1	->SetPos(860.0f, 430.0f, 0.0f);
		coinNum10	->SetPos(800.0f, 430.0f, 0.0f);
		coinNum100	->SetPos(740.0f, 430.0f, 0.0f);

		// コイン獲得数オブジェクトのタグ付け
		coinNum1	->tags.AddTag("1");
		coinNum10	->tags.AddTag("10");
		coinNum100	->tags.AddTag("100");
		
		for (auto& obj : objectInstance)
		{
			obj->Init();
		}
		break; }
	case 2: {
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// サウンドを停止
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// サウンドを停止
		SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// サウンドを再生

		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_2.png");
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
			{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
		break; }
	case 3: {
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// サウンドを停止
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// サウンドを停止
		SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// サウンドを再生

		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_3.jpg");
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
			{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
		break; }
	case 4: {
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// サウンドを停止
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// サウンドを停止
		SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// サウンドを再生

		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_4.png");
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
			{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
		break; }
	case 5: {
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// サウンドを停止
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// サウンドを停止
		SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// サウンドを再生

		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_5.jpg");
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
			{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
		break; }
	case 6: {
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// サウンドを停止
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// サウンドを停止
		SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// サウンドを再生

		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_6.png");
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
			{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
		break; }
	case 7: {
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// サウンドを停止
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// サウンドを停止
		SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// サウンドを再生

		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_7.jpg");
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
			{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
		break; }
	case 8: {
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// サウンドを停止
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// サウンドを停止
		SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// サウンドを再生

		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_8.png");
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
			{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
		break; }
	default:
		break;
	}
}

void GameScene::Update()
{
	// コイン獲得数UIの各桁更新処理
	auto coinUIs = GetInstance()->GetObjects<CoinNum>();
	for (auto& coinUI : coinUIs)
	{
		if (coinUI->tags.SearchTag("100")) {
			int coinCount = 0;
			coinCount = GameScene::bandTipCount / 100;
			if (coinCount >= 10) { coinCount -= 10; }
			coinUI->SetNumU(coinCount);
		}
		if (coinUI->tags.SearchTag("10")) {
			int coinCount = 0;
			coinCount = GameScene::bandTipCount / 10;
			if (coinCount >= 10) { coinCount -= 10; }
			coinUI->SetNumU(coinCount);
		}
		
		if (coinUI->tags.SearchTag("1")) {
			int coinCount = 0;
			coinCount = GameScene::bandTipCount % 10;
			coinUI->SetNumU(coinCount);
		}
	}

	auto objects = objectInstance;
	for (auto& obj : objects)
	{
		obj->Update();
	}

	auto players =GetInstance()->GetObjects<Player>();
	for (auto& player : players)
	{
		if (GROUND_OFFSET_Y > player->GetPos().y + 120.0f)
		{
			SceneManager::ChangeScene(GAMEOVER);
		}
	}
}