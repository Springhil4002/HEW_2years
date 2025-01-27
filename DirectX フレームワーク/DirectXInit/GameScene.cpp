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
#include "MapEditor.h"

//#include "iostream"

Object* GameScene::player = nullptr;

int GameScene::bandTipCount = 0;			// bandTipの獲得数
int GameScene::allBandTipCount = 0;			// bandTipの総数

void GameScene::Init(int _num)
{	
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// サウンドを停止
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// サウンドを停止
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM005);	// サウンドを停止
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// サウンドを再生

	bandTipCount = 0;		// 獲得数を初期化
	allBandTipCount = 0;	// ステージ内にあるコインの総数
	gameSceneNum = _num;
	GameOverScene::isEndSceneNum = (SCENE)(gameSceneNum + SCENE_ENUM_OFFSET);
	switch(gameSceneNum)
	{
	case 1: {

		// 背景オブジェクトの作成
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_1.jpg");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -1;

		// Stage1のCSV読み込み
		MapEditor::Load("Stage1.csv");
		
		// コイン獲得数オブジェクトの作成
		auto coinNum1	= Object::Create<CoinNum>();
		auto coinNum10	= Object::Create<CoinNum>();
		auto coinNum100 = Object::Create<CoinNum>();
		
		// コイン獲得数オブジェクトの座標設定
		coinNum1	->SetPos(900.0f, 480.0f, 0.0f);
		coinNum10	->SetPos(840.0f, 480.0f, 0.0f);
		coinNum100	->SetPos(780.0f, 480.0f, 0.0f);
		
		// コイン獲得数オブジェクトの大きさを設定
		coinNum1	->SetScale(50.0f, 100.0f, 0.0f);						
		coinNum10	->SetScale(50.0f, 100.0f, 0.0f);
		coinNum100	->SetScale(50.0f, 100.0f, 0.0f);

		// コイン獲得数オブジェクトのタグ付け
		coinNum1	->tags.AddTag("一の位");
		coinNum10	->tags.AddTag("十の位");
		coinNum100	->tags.AddTag("百の位");
		
		break; }
	case 2: {

		// 背景オブジェクトの作成
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_2.png");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -1;

		// Stage2のCSV読み込み

		// コイン獲得数オブジェクトの作成
		auto coinNum1 = Object::Create<CoinNum>();
		auto coinNum10 = Object::Create<CoinNum>();
		auto coinNum100 = Object::Create<CoinNum>();

		// コイン獲得数オブジェクトの座標設定
		coinNum1->SetPos(900.0f, 480.0f, 0.0f);
		coinNum10->SetPos(840.0f, 480.0f, 0.0f);
		coinNum100->SetPos(780.0f, 480.0f, 0.0f);

		// コイン獲得数オブジェクトの大きさを設定
		coinNum1->SetScale(50.0f, 100.0f, 0.0f);
		coinNum10->SetScale(50.0f, 100.0f, 0.0f);
		coinNum100->SetScale(50.0f, 100.0f, 0.0f);

		// コイン獲得数オブジェクトのタグ付け
		coinNum1->tags.AddTag("一の位");
		coinNum10->tags.AddTag("十の位");
		coinNum100->tags.AddTag("百の位");

		break; }
	case 3: {
	
		// 背景オブジェクトの作成
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_3.jpg");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -1;
		
		// Stage3のCSV読み込み

		// コイン獲得数オブジェクトの作成
		auto coinNum1 = Object::Create<CoinNum>();
		auto coinNum10 = Object::Create<CoinNum>();
		auto coinNum100 = Object::Create<CoinNum>();

		// コイン獲得数オブジェクトの座標設定
		coinNum1->SetPos(900.0f, 480.0f, 0.0f);
		coinNum10->SetPos(840.0f, 480.0f, 0.0f);
		coinNum100->SetPos(780.0f, 480.0f, 0.0f);

		// コイン獲得数オブジェクトの大きさを設定
		coinNum1->SetScale(50.0f, 100.0f, 0.0f);
		coinNum10->SetScale(50.0f, 100.0f, 0.0f);
		coinNum100->SetScale(50.0f, 100.0f, 0.0f);

		// コイン獲得数オブジェクトのタグ付け
		coinNum1->tags.AddTag("一の位");
		coinNum10->tags.AddTag("十の位");
		coinNum100->tags.AddTag("百の位");

		break; }
	case 4: {
	
		// 背景オブジェクトの作成
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_4.png");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -1;

		// Stage4のCSV読み込み

		// コイン獲得数オブジェクトの作成
		auto coinNum1 = Object::Create<CoinNum>();
		auto coinNum10 = Object::Create<CoinNum>();
		auto coinNum100 = Object::Create<CoinNum>();

		// コイン獲得数オブジェクトの座標設定
		coinNum1->SetPos(900.0f, 480.0f, 0.0f);
		coinNum10->SetPos(840.0f, 480.0f, 0.0f);
		coinNum100->SetPos(780.0f, 480.0f, 0.0f);

		// コイン獲得数オブジェクトの大きさを設定
		coinNum1->SetScale(50.0f, 100.0f, 0.0f);
		coinNum10->SetScale(50.0f, 100.0f, 0.0f);
		coinNum100->SetScale(50.0f, 100.0f, 0.0f);

		// コイン獲得数オブジェクトのタグ付け
		coinNum1->tags.AddTag("一の位");
		coinNum10->tags.AddTag("十の位");
		coinNum100->tags.AddTag("百の位");
		break; }
	case 5: {
		
		// 背景オブジェクトの作成
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_5.jpg");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -1;
		
		// Stage5のCSV読み込み

		// コイン獲得数オブジェクトの作成
		auto coinNum1 = Object::Create<CoinNum>();
		auto coinNum10 = Object::Create<CoinNum>();
		auto coinNum100 = Object::Create<CoinNum>();

		// コイン獲得数オブジェクトの座標設定
		coinNum1->SetPos(900.0f, 480.0f, 0.0f);
		coinNum10->SetPos(840.0f, 480.0f, 0.0f);
		coinNum100->SetPos(780.0f, 480.0f, 0.0f);

		// コイン獲得数オブジェクトの大きさを設定
		coinNum1->SetScale(50.0f, 100.0f, 0.0f);
		coinNum10->SetScale(50.0f, 100.0f, 0.0f);
		coinNum100->SetScale(50.0f, 100.0f, 0.0f);

		// コイン獲得数オブジェクトのタグ付け
		coinNum1->tags.AddTag("一の位");
		coinNum10->tags.AddTag("十の位");
		coinNum100->tags.AddTag("百の位");

		break; }
	case 6: {
		
		// 背景オブジェクトの作成
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_6.png");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -1;

		// Stage6のCSV読み込み

		// コイン獲得数オブジェクトの作成
		auto coinNum1 = Object::Create<CoinNum>();
		auto coinNum10 = Object::Create<CoinNum>();
		auto coinNum100 = Object::Create<CoinNum>();

		// コイン獲得数オブジェクトの座標設定
		coinNum1->SetPos(900.0f, 480.0f, 0.0f);
		coinNum10->SetPos(840.0f, 480.0f, 0.0f);
		coinNum100->SetPos(780.0f, 480.0f, 0.0f);

		// コイン獲得数オブジェクトの大きさを設定
		coinNum1->SetScale(50.0f, 100.0f, 0.0f);
		coinNum10->SetScale(50.0f, 100.0f, 0.0f);
		coinNum100->SetScale(50.0f, 100.0f, 0.0f);

		// コイン獲得数オブジェクトのタグ付け
		coinNum1->tags.AddTag("一の位");
		coinNum10->tags.AddTag("十の位");
		coinNum100->tags.AddTag("百の位");

		break; }
	case 7: {
	
		// 背景オブジェクトの作成
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_7.jpg");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -1;

		// Stage7のCSV読み込み

		// コイン獲得数オブジェクトの作成
		auto coinNum1 = Object::Create<CoinNum>();
		auto coinNum10 = Object::Create<CoinNum>();
		auto coinNum100 = Object::Create<CoinNum>();

		// コイン獲得数オブジェクトの座標設定
		coinNum1->SetPos(900.0f, 480.0f, 0.0f);
		coinNum10->SetPos(840.0f, 480.0f, 0.0f);
		coinNum100->SetPos(780.0f, 480.0f, 0.0f);

		// コイン獲得数オブジェクトの大きさを設定
		coinNum1->SetScale(50.0f, 100.0f, 0.0f);
		coinNum10->SetScale(50.0f, 100.0f, 0.0f);
		coinNum100->SetScale(50.0f, 100.0f, 0.0f);

		// コイン獲得数オブジェクトのタグ付け
		coinNum1->tags.AddTag("一の位");
		coinNum10->tags.AddTag("十の位");
		coinNum100->tags.AddTag("百の位");

		break; }
	case 8: {
	
		// 背景オブジェクトの作成
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_8.png");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -1;

		// Stage8のCSV読み込み

		// コイン獲得数オブジェクトの作成
		auto coinNum1 = Object::Create<CoinNum>();
		auto coinNum10 = Object::Create<CoinNum>();
		auto coinNum100 = Object::Create<CoinNum>();

		// コイン獲得数オブジェクトの座標設定
		coinNum1->SetPos(900.0f, 480.0f, 0.0f);
		coinNum10->SetPos(840.0f, 480.0f, 0.0f);
		coinNum100->SetPos(780.0f, 480.0f, 0.0f);

		// コイン獲得数オブジェクトの大きさを設定
		coinNum1->SetScale(50.0f, 100.0f, 0.0f);
		coinNum10->SetScale(50.0f, 100.0f, 0.0f);
		coinNum100->SetScale(50.0f, 100.0f, 0.0f);

		// コイン獲得数オブジェクトのタグ付け
		coinNum1->tags.AddTag("一の位");
		coinNum10->tags.AddTag("十の位");
		coinNum100->tags.AddTag("百の位");

		break; }
	default:
		break;
	}
}

void GameScene::Update()
{
	// コイン獲得数UIの各桁更新処理
	CoinCounter();
	// コイン獲得数UIの各桁更新処理
	FallIsPlayer();
	
	auto objects = objectInstance;
	for (auto& obj : objects)
	{
		obj->Update();
	}
}

// コイン獲得数UIの各桁更新処理
void GameScene::CoinCounter()
{
	auto coinUIs = GetInstance()->GetObjects<CoinNum>();
	for (auto& coinUI : coinUIs)
	{
		if (coinUI->tags.SearchTag("百の位")) {
			int coinCount = 0;
			coinCount = GameScene::bandTipCount / 100;
			if (coinCount >= 10) { coinCount -= 10; }
			coinUI->SetNumU(coinCount);
		}
		if (coinUI->tags.SearchTag("十の位")) {
			int coinCount = 0;
			coinCount = GameScene::bandTipCount / 10;
			if (coinCount >= 10) { coinCount -= 10; }
			coinUI->SetNumU(coinCount);
		}

		if (coinUI->tags.SearchTag("一の位")) {
			int coinCount = 0;
			coinCount = GameScene::bandTipCount % 10;
			coinUI->SetNumU(coinCount);
		}
	}
}

// playerの落下判定処理と遷移処理
void GameScene::FallIsPlayer()
{
	auto players = GetInstance()->GetObjects<Player>();
	for (auto& player : players)
	{
		if (GROUND_OFFSET_Y > player->GetPos().y + 120.0f)
		{
			SceneManager::ChangeScene(GAMEOVER);
		}
	}
}