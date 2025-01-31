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
#include "Application.h"

//#include "iostream"

Player* GameScene::player = nullptr;

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
		bg->layer = -5;

		// フェードイン・フェードアウト
		auto fade = Object::Create<Quad>();
		fade->SetTex("asset/Texture/Fade.png");						// 画像読み込み
		fade->SetPos(0.0f, 0.0f, 0.0f);								// 座標設定
		fade->SetScale(1920.0f, 1080.0f, 0.0f);						// 大きさを設定
		fade->tags.AddTag("Fade");									// タグ付け
		fade->layer = 10;											// レイヤーを設定

		// フェードイン・フェードアウト(ゲームオーバー)	
		auto fade_GameOver = Object::Create<Quad>();
		fade_GameOver->SetTex("asset/Texture/Fade_Black.png");			// 画像読み込み
		fade_GameOver->SetPos(0.0f, 0.0f, 0.0f);						// 座標設定
		fade_GameOver->SetScale(1920.0f, 1080.0f, 0.0f);				// 大きさを設定
		fade_GameOver->SetColor(1.0f, 1.0f, 1.0f, 0.0f);				// 色設定
		fade_GameOver->tags.AddTag("Fade_GameOver");					// タグ付け
		fade_GameOver->layer = -10;										// レイヤーを設定

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
		
		// リトライUI表示オブジェクト作成
		auto retry = Object::Create<Quad>();
		retry->SetTex("asset/Texture/Retry_UI.png");			// 画像読み込み
		retry->SetPos(-900.0f, 480.0f, 0.0f);					// 座標設定
		retry->SetScale(100.0f, 100.0f, 100.0f);				// 大きさを設定
		retry->tags.AddTag("Retry");							// タグ付け

		break; }
	case 2: {

		// 背景オブジェクトの作成
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_2.png");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -5;

		// フェードイン・フェードアウト
		auto fade = Object::Create<Quad>();
		fade->SetTex("asset/Texture/Fade.png");						// 画像読み込み
		fade->SetPos(0.0f, 0.0f, 0.0f);								// 座標設定
		fade->SetScale(1920.0f, 1080.0f, 0.0f);						// 大きさを設定
		fade->tags.AddTag("Fade");									// タグ付け
		fade->layer = 10;											// レイヤーを設定

		// フェードイン・フェードアウト(ゲームオーバー)	
		auto fade_GameOver = Object::Create<Quad>();
		fade_GameOver->SetTex("asset/Texture/Fade_Black.png",			// 画像読み込み
			1, 1, 0, 0, 1.0f, 1.0f, 1.0f, 0.0f);
		fade_GameOver->SetPos(0.0f, 0.0f, 0.0f);						// 座標設定
		fade_GameOver->SetScale(1920.0f, 1080.0f, 0.0f);				// 大きさを設定
		fade_GameOver->tags.AddTag("Fade_GameOver");					// タグ付け
		fade_GameOver->layer = -10;										// レイヤーを設定

		// Stage2のCSV読み込み
		MapEditor::Load("Stage2.csv");

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

		// リトライUI表示オブジェクト作成
		auto retry = Object::Create<Quad>();					// 画像読み込み
		retry->SetTex("asset/Texture/Retry_UI.png");			// 画像読み込み
		retry->SetPos(-900.0f, 480.0f, 0.0f);					// 座標設定
		retry->SetScale(100.0f, 100.0f, 100.0f);				// 大きさを設定
		retry->tags.AddTag("Retry");							// タグ付け

		break; }
	case 3: {
	
		// 背景オブジェクトの作成
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_3.jpg");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -5;

		// フェードイン・フェードアウト
		auto fade = Object::Create<Quad>();
		fade->SetTex("asset/Texture/Fade.png");						// 画像読み込み
		fade->SetPos(0.0f, 0.0f, 0.0f);								// 座標設定
		fade->SetScale(1920.0f, 1080.0f, 0.0f);						// 大きさを設定
		fade->tags.AddTag("Fade");									// タグ付け
		fade->layer = 10;											// レイヤーを設定
		
		// フェードイン・フェードアウト(ゲームオーバー)	
		auto fade_GameOver = Object::Create<Quad>();
		fade_GameOver->SetTex("asset/Texture/Fade_Black.png",			// 画像読み込み
			1, 1, 0, 0, 1.0f, 1.0f, 1.0f, 0.0f);
		fade_GameOver->SetPos(0.0f, 0.0f, 0.0f);						// 座標設定
		fade_GameOver->SetScale(1920.0f, 1080.0f, 0.0f);				// 大きさを設定
		fade_GameOver->tags.AddTag("Fade_GameOver");					// タグ付け
		fade_GameOver->layer = -10;										// レイヤーを設定

		// Stage3のCSV読み込み
		MapEditor::Load("Stage3.csv");

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

		// リトライUI表示オブジェクト作成
		auto retry = Object::Create<Quad>();					// 画像読み込み
		retry->SetTex("asset/Texture/Retry_UI.png");			// 画像読み込み
		retry->SetPos(-900.0f, 480.0f, 0.0f);					// 座標設定
		retry->SetScale(100.0f, 100.0f, 100.0f);				// 大きさを設定
		retry->tags.AddTag("Retry");							// タグ付け

		break; }
	case 4: {
	
		// 背景オブジェクトの作成
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_4.png");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -5;

		// フェードイン・フェードアウト
		auto fade = Object::Create<Quad>();
		fade->SetTex("asset/Texture/Fade.png");						// 画像読み込み
		fade->SetPos(0.0f, 0.0f, 0.0f);								// 座標設定
		fade->SetScale(1920.0f, 1080.0f, 0.0f);						// 大きさを設定
		fade->tags.AddTag("Fade");									// タグ付け
		fade->layer = 10;											// レイヤーを設定

		// フェードイン・フェードアウト(ゲームオーバー)	
		auto fade_GameOver = Object::Create<Quad>();
		fade_GameOver->SetTex("asset/Texture/Fade_Black.png",			// 画像読み込み
			1, 1, 0, 0, 1.0f, 1.0f, 1.0f, 0.0f);
		fade_GameOver->SetPos(0.0f, 0.0f, 0.0f);						// 座標設定
		fade_GameOver->SetScale(1920.0f, 1080.0f, 0.0f);				// 大きさを設定
		fade_GameOver->tags.AddTag("Fade_GameOver");					// タグ付け
		fade_GameOver->layer = -10;										// レイヤーを設定

		// Stage4のCSV読み込み
		MapEditor::Load("Stage4.csv");

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

		// リトライUI表示オブジェクト作成
		auto retry = Object::Create<Quad>();					// 画像読み込み
		retry->SetTex("asset/Texture/Retry_UI.png");			// 画像読み込み
		retry->SetPos(-900.0f, 480.0f, 0.0f);					// 座標設定
		retry->SetScale(100.0f, 100.0f, 100.0f);				// 大きさを設定
		retry->tags.AddTag("Retry");							// タグ付け

		break; }
	case 5: {
		
		// 背景オブジェクトの作成
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_5.jpg");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -5;
		
		// フェードイン・フェードアウト
		auto fade = Object::Create<Quad>();
		fade->SetTex("asset/Texture/Fade.png");						// 画像読み込み
		fade->SetPos(0.0f, 0.0f, 0.0f);								// 座標設定
		fade->SetScale(1920.0f, 1080.0f, 0.0f);						// 大きさを設定
		fade->tags.AddTag("Fade");									// タグ付け
		fade->layer = 10;											// レイヤーを設定

		// フェードイン・フェードアウト(ゲームオーバー)	
		auto fade_GameOver = Object::Create<Quad>();
		fade_GameOver->SetTex("asset/Texture/Fade_Black.png",			// 画像読み込み
			1, 1, 0, 0, 1.0f, 1.0f, 1.0f, 0.0f);
		fade_GameOver->SetPos(0.0f, 0.0f, 0.0f);						// 座標設定
		fade_GameOver->SetScale(1920.0f, 1080.0f, 0.0f);				// 大きさを設定
		fade_GameOver->tags.AddTag("Fade_GameOver");					// タグ付け
		fade_GameOver->layer = -10;										// レイヤーを設定

		// Stage5のCSV読み込み
		MapEditor::Load("Stage5.csv");

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

		// リトライUI表示オブジェクト作成
		auto retry = Object::Create<Quad>();					// 画像読み込み
		retry->SetTex("asset/Texture/Retry_UI.png");			// 画像読み込み
		retry->SetPos(-900.0f, 480.0f, 0.0f);					// 座標設定
		retry->SetScale(100.0f, 100.0f, 100.0f);				// 大きさを設定
		retry->tags.AddTag("Retry");							// タグ付け

		break; }
	case 6: {
		
		// 背景オブジェクトの作成
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_6.png");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -5;

		// フェードイン・フェードアウト
		auto fade = Object::Create<Quad>();
		fade->SetTex("asset/Texture/Fade.png");						// 画像読み込み
		fade->SetPos(0.0f, 0.0f, 0.0f);								// 座標設定
		fade->SetScale(1920.0f, 1080.0f, 0.0f);						// 大きさを設定
		fade->tags.AddTag("Fade");									// タグ付け
		fade->layer = 10;											// レイヤーを設定

		// フェードイン・フェードアウト(ゲームオーバー)	
		auto fade_GameOver = Object::Create<Quad>();
		fade_GameOver->SetTex("asset/Texture/Fade_Black.png",			// 画像読み込み
			1, 1, 0, 0, 1.0f, 1.0f, 1.0f, 0.0f);
		fade_GameOver->SetPos(0.0f, 0.0f, 0.0f);						// 座標設定
		fade_GameOver->SetScale(1920.0f, 1080.0f, 0.0f);				// 大きさを設定
		fade_GameOver->tags.AddTag("Fade_GameOver");					// タグ付け
		fade_GameOver->layer = -10;										// レイヤーを設定

		// Stage6のCSV読み込み
		MapEditor::Load("Stage6.csv");

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

		// リトライUI表示オブジェクト作成
		auto retry = Object::Create<Quad>();					// 画像読み込み
		retry->SetTex("asset/Texture/Retry_UI.png");			// 画像読み込み
		retry->SetPos(-900.0f, 480.0f, 0.0f);					// 座標設定
		retry->SetScale(100.0f, 100.0f, 100.0f);				// 大きさを設定
		retry->tags.AddTag("Retry");							// タグ付け

		break; }
	case 7: {
	
		// 背景オブジェクトの作成
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_7.jpg");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -5;

		// フェードイン・フェードアウト
		auto fade = Object::Create<Quad>();
		fade->SetTex("asset/Texture/Fade.png");						// 画像読み込み
		fade->SetPos(0.0f, 0.0f, 0.0f);								// 座標設定
		fade->SetScale(1920.0f, 1080.0f, 0.0f);						// 大きさを設定
		fade->tags.AddTag("Fade");									// タグ付け
		fade->layer = 10;											// レイヤーを設定

		// フェードイン・フェードアウト(ゲームオーバー)	
		auto fade_GameOver = Object::Create<Quad>();
		fade_GameOver->SetTex("asset/Texture/Fade_Black.png",			// 画像読み込み
			1, 1, 0, 0, 1.0f, 1.0f, 1.0f, 0.0f);
		fade_GameOver->SetPos(0.0f, 0.0f, 0.0f);						// 座標設定
		fade_GameOver->SetScale(1920.0f, 1080.0f, 0.0f);				// 大きさを設定
		fade_GameOver->tags.AddTag("Fade_GameOver");					// タグ付け
		fade_GameOver->layer = -10;										// レイヤーを設定

		// Stage7のCSV読み込み
		MapEditor::Load("Stage7.csv");

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

		// リトライUI表示オブジェクト作成
		auto retry = Object::Create<Quad>();					// 画像読み込み
		retry->SetTex("asset/Texture/Retry_UI.png");			// 画像読み込み
		retry->SetPos(-900.0f, 480.0f, 0.0f);					// 座標設定
		retry->SetScale(100.0f, 100.0f, 100.0f);				// 大きさを設定
		retry->tags.AddTag("Retry");							// タグ付け

		break; }
	case 8: {
	
		// 背景オブジェクトの作成
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_8.png");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -5;

		// フェードイン・フェードアウト
		auto fade = Object::Create<Quad>();
		fade->SetTex("asset/Texture/Fade.png");						// 画像読み込み
		fade->SetPos(0.0f, 0.0f, 0.0f);								// 座標設定
		fade->SetScale(1920.0f, 1080.0f, 0.0f);						// 大きさを設定
		fade->tags.AddTag("Fade");									// タグ付け
		fade->layer = 10;											// レイヤーを設定

		// フェードイン・フェードアウト(ゲームオーバー)	
		auto fade_GameOver = Object::Create<Quad>();
		fade_GameOver->SetTex("asset/Texture/Fade_Black.png",			// 画像読み込み
			1, 1, 0, 0, 1.0f, 1.0f, 1.0f, 0.0f);
		fade_GameOver->SetPos(0.0f, 0.0f, 0.0f);						// 座標設定
		fade_GameOver->SetScale(1920.0f, 1080.0f, 0.0f);				// 大きさを設定
		fade_GameOver->tags.AddTag("Fade_GameOver");					// タグ付け
		fade_GameOver->layer = -10;										// レイヤーを設定

		// Stage8のCSV読み込み
		MapEditor::Load("Stage8.csv");

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

		// リトライUI表示オブジェクト作成
		auto retry = Object::Create<Quad>();					// 画像読み込み
		retry->SetTex("asset/Texture/Retry_UI.png");			// 画像読み込み
		retry->SetPos(-900.0f, 480.0f, 0.0f);					// 座標設定
		retry->SetScale(100.0f, 100.0f, 100.0f);				// 大きさを設定
		retry->tags.AddTag("Retry");							// タグ付け

		break; }
	default:
		break;
	}
}

void GameScene::Update()
{
	if (fade_In == true)
	{
		// フェードイン処理		(明るくなる)
		Fade_In();
	}
	// コイン獲得数UIの各桁更新処理
	CoinCounter();
	// コイン獲得数UIの各桁更新処理
	FallIsPlayer();
	// ゲーム中のリトライ機能
	RetryGame();
	if (fadeOut_Start == true)
	{
		Fade_Out();	// フェードアウト処理	(暗くなる)
	}
	if (fadeOut_Start_GameOver == true)
	{
		Fade_Out_GameOver();	// フェードアウト(ゲームオーバー)
	}
	
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
			fadeOut_Start_GameOver = true;
		}
	}
	if (fadeOut_End_GameOver == true)
	{
		SceneManager::ChangeScene(GAMEOVER);
	}
}


// フェードイン処理		(明るくなる)
void GameScene::Fade_In()
{
	if (Application::GetFpsCounter() % 6 == 0)
	{
		countFadeIn += 1;
		auto Fade = GetInstance()->GetObjects<Quad>();
		for (auto& fade : Fade)
		{
			if (fade->tags.SearchTag("Fade"))
			{
				switch (countFadeIn)
				{
				case 1: {
					fade->SetTex("asset/Texture/Fade/Fade_In_1.png");	// 画像読み込み
					break; }
				case 2: {
					fade->SetTex("asset/Texture/Fade/Fade_In_2.png");	// 画像読み込み
					break; }
				case 3: {
					fade->SetTex("asset/Texture/Fade/Fade_In_3.png");	// 画像読み込み
					break; }
				case 4: {
					fade->SetTex("asset/Texture/Fade/Fade_In_4.png");	// 画像読み込み
					break; }
				case 5: {
					fade->SetTex("asset/Texture/Fade/Fade_In_5.png");	// 画像読み込み
					break; }
				case 6: {
					fade->SetTex("asset/Texture/Fade/Fade_In_6.png");	// 画像読み込み
					break; }
				case 7: {
					fade->SetTex("asset/Texture/Fade/Fade_In_7.png");	// 画像読み込み
					break; }
				case 8: {
					fade->SetTex("asset/Texture/Fade/Fade_In_8.png");	// 画像読み込み
					break; }
				case 9: {
					fade->SetTex("asset/Texture/Fade/Fade_In_9.png");	// 画像読み込み
					break; }
				case 10: {
					fade->SetTex("asset/Texture/Fade/Fade_In_10.png");	// 画像読み込み
					break; }
				default: {
					fade->SetColor(1.0f, 1.0f, 1.0f, 0.0f);
					fade->SetTex("asset/Texture/Fade.png");		// 画像読み込み
					fade_In = false;							// フェードイン終了
					break; }
				}
			}
		}
	}
}

// フェードアウト処理	(暗くなる)
void GameScene::Fade_Out()
{
	if (Application::GetFpsCounter() % 6 == 0)
	{
		countFadeOut += 1;
		auto Fade = GetInstance()->GetObjects<Quad>();
		for (auto& fade : Fade)
		{
			if (fade->tags.SearchTag("Fade"))
			{
				fade->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
				switch (countFadeOut)
				{
				case 1: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_1.png");	// 画像読み込み
					break; }
				case 2: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_2.png");	// 画像読み込み
					break; }
				case 3: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_3.png");	// 画像読み込み
					break; }
				case 4: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_4.png");	// 画像読み込み
					break; }
				case 5: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_5.png");	// 画像読み込み
					break; }
				case 6: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_6.png");	// 画像読み込み
					break; }
				case 7: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_7.png");	// 画像読み込み
					break; }
				case 8: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_8.png");	// 画像読み込み
					break; }
				case 9: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_9.png");	// 画像読み込み
					break; }
				case 10: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_10.png");	// 画像読み込み
					break; }
				default: {
					fade->SetTex("asset/Texture/Fade.png");		// 画像読み込み
					fadeOut_End = true;
					break; }
				}
			}
		}
	}
}

// ゲーム中のリトライ機能
void GameScene::RetryGame()
{
	if(input.GetKeyTrigger(VK_R)||
	   input.GetButtonTrigger(XINPUT_START))
	{
		int stageNum = (int)(GameOverScene::isEndSceneNum - SCENE_ENUM_OFFSET);					
		SceneManager::ChangeScene(GameOverScene::isEndSceneNum, stageNum);
	}
}

void GameScene::Fade_Out_GameOver()
{
	auto Fade = GetInstance()->GetObjects<Quad>();
	for (auto& fade : Fade)
	{
		if (fade->tags.SearchTag("Fade_GameOver"))
		{
			fade->layer = 10;
			if (fade->GetColor().w <= 1.0f)
			{
				fade->SetColor(1.0f, 1.0f, 1.0f, fade->GetColor().w + 0.05f);
			}
			else
			{
				fadeOut_End_GameOver = true;
			}
		}
	}
}