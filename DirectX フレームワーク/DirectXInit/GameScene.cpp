#include "GameScene.h"
#include "GameOverScene.h"
#include "SceneManager.h"
#include "Quad.h"
#include "Ground.h"
#include "Player.h"
#include "Band.h"
#include "Coin.h"

//コンストラクタ
GameScene::GameScene(int _num) 
{
	Init(_num); 
}	

GameScene::~GameScene()
{
	
}

void GameScene::Init(int _num)
{	
	gameSceneNum = _num;
	GameOverScene::isEndSceneNum = (SCENE)(gameSceneNum + 2);
	switch(gameSceneNum)
	{
	case 1: {
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// サウンドを停止
		SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// サウンドを再生

		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_1.jpg");
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
			{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
	case 2: {
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// サウンドを停止
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
			{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
			{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
			{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
			{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
			{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
			{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
			{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
		SceneManager::ChangeScene(RESULT);
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
