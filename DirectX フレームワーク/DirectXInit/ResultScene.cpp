#include "ResultScene.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "Quad.h"
#include "Ground.h"
#include "Player.h"
#include "Band.h"
#include "CoinNum.h"
#include "StarTip.h"

#include "iostream"

int ResultScene::tipCount = 0;
int ResultScene::meterCount = 0;

// 初期化処理
void ResultScene::Init(int _num)
{
	tipCount = _num;										// コイン獲得数を設定
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM003);	// サウンドを停止
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM005);	// サウンドを再生

	// 背景オブジェクトの作成
	auto bg = Object::Create<Quad>();
	bg->SetTex("asset/Texture/Night_Loom.jpg");
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
	bg->layer = -1;

	// フェードイン・フェードアウト用
	auto fade = Object::Create<Quad>();
	fade->SetTex("asset/Texture/Fade_Black.png",			// 画像読み込み
		1, 1, 0, 0, 1.0f, 1.0f, 1.0f, 1.0f);
	fade->SetPos(0.0f, 0.0f, 0.0f);							// 座標設定
	fade->SetScale(1920.0f, 1080.0f, 0.0f);					// 大きさを設定
	fade->tags.AddTag("Fade");								// タグ付け
	fade->layer = 10;										// レイヤーを設定

	// プレイヤーオブジェクトの作成
	auto player = Object::Create<Player>();
	player->SetPos(-800.0f, -400.0f, 0.0f);

	// CLEARのロゴオブジェクトの作成
	auto clear_Logo = Object::Create<Quad>();
	clear_Logo->SetTex("asset/Texture/Clear_Logo.png");
	clear_Logo->SetPos(0.0f, 0.0f, 0.0f);
	clear_Logo->SetScale(0.0f, 0.0f, 0.0f);
	clear_Logo->tags.AddTag("CLEAR");
	clear_Logo->layer = 1;

	// 地面オブジェクトの作成
	Ground* ground[SET_BLOCK];
	for(int i = 0; i < SET_BLOCK; i++)
	{
		ground[i] = Object::Create<Ground>();
		ground[i]->SetPos(930.0f - (i * BLOCK_SIZE), -510.0f, 0.0f);
	}

	// 結束バンドオブジェクトの作成
	auto band = Object::Create<Band>();
	band->SetTex("asset/Texture/Band_Block.png");
	band->SetPos(30.0f, -450.0f, 0.0f);
	band->SetScale(BLOCK_SIZE, BLOCK_SIZE, 0.0f);
	band->layer = 1;
	band->SetLength(tipCount);

	// コイン獲得数オブジェクトの作成
	auto coinNum1 = Object::Create<CoinNum>();
	auto coinNum10 = Object::Create<CoinNum>();
	auto coinNum100 = Object::Create<CoinNum>();

	// コイン獲得数オブジェクトの座標設定
	coinNum1->SetPos(150.0f, 0.0f, 0.0f);
	coinNum10->SetPos(0.0f, 0.0f, 0.0f);
	coinNum100->SetPos(-150.0f, 0.0f, 0.0f);

	// コイン獲得数の拡大表示
	coinNum1->SetScale(150.0f, 300.0f, 0.0f);
	coinNum10->SetScale(150.0f, 300.0f, 0.0f);
	coinNum100->SetScale(150.0f, 300.0f, 0.0f);

	// コイン獲得数オブジェクトのタグ付け
	coinNum1->tags.AddTag("一の位");
	coinNum10->tags.AddTag("十の位");
	coinNum100->tags.AddTag("百の位");

	// スターチップオブジェクトの作成
	StarTip* starTip[SET_STARTIP];
	for (int i = 0; i < SET_STARTIP; i++)
	{
		starTip[i] = Object::Create<StarTip>();
		starTip[i]->SetPos(-300.0f + (i * BLOCK_SIZE * 5), 300.0f, 0.0f);
		switch (i)
		{
		case 0:
			starTip[i]->tags.AddTag("1枚目");
			break;
		case 1:
			starTip[i]->tags.AddTag("2枚目");
			break;
		case 2:
			starTip[i]->tags.AddTag("3枚目");
			break;
		}
	}
	for (auto& obj : objectInstance)
	{
		obj->Init();
	}
}

// 更新処理
void ResultScene::Update()
{
	// フェードイン処理
	Fade_In();

	// 引っ張った長さに応じてスコアを更新
	PullScoreUpdate();

	// コイン獲得数UIの各桁更新処理
	CoinCounter();

	// コイン獲得数の割合に応じてStarTipの獲得状況の更新
	CoinGetPercent();

	// CLEARロゴの拡大表示と表示後の移動
	ClearDraw();

	// UIが描画OKなら
	if (uiFlag == true)
	{
		UI_Draw();
	}

	// フレーム更新処理
	Frame_Update();

	// フェードアウト処理	(暗くなる)
	if (fadeOut_Start == true)
	{
		Fade_Out();
	}

	// 各オブジェクト更新処理
	auto objects = objectInstance;
	for (auto& obj : objects)
	{
		if (obj->tags.SearchTag("Player"))
		{
			if (movePlayerFlag == true)
			{
				obj->Update();
			}
		}
		else
		{
			obj->Update();
		}
	}
}

// 引っ張った長さに応じてスコアを更新
void ResultScene::PullScoreUpdate()
{
	auto bandPullLevels = GetInstance()->GetObjects<Band>();
	for (auto& bandPullLevel : bandPullLevels)
	{
		meterCount = (int)(bandPullLevel->GetPullLevel() / -60.0f);
	}
}

// コイン獲得数UIの各桁更新処理
void ResultScene::CoinCounter()
{
	auto coinUIs = GetInstance()->GetObjects<CoinNum>();
	for (auto& coinUI : coinUIs)
	{
		if (coinUI->tags.SearchTag("百の位")) {
			int coinCount = 0;
			coinCount = meterCount / 100;
			if (coinCount >= 10) { coinCount -= 10; }
			coinUI->SetNumU(coinCount);
		}
		if (coinUI->tags.SearchTag("十の位")) {
			int coinCount = 0;
			coinCount = meterCount / 10;
			if (coinCount >= 10) { coinCount -= 10; }
			coinUI->SetNumU(coinCount);
		}
		if (coinUI->tags.SearchTag("一の位")) {
			int coinCount = 0;
			coinCount = meterCount % 10;
			coinUI->SetNumU(coinCount);
		}
	}
}

// コイン獲得数の割合に応じてStarTipの獲得状況の更新
void ResultScene::CoinGetPercent()
{
	auto star_s = GetInstance()->GetObjects<StarTip>();
	for (auto& star : star_s)
	{
		if (star->tags.SearchTag("1枚目"))
		{
			if (meterCount >=(GameScene::GetAllBandTipCount() * 3 / 10))
			{
				star->SetGeting(true);
			}
		}
		if (star->tags.SearchTag("2枚目"))
		{
			if (meterCount >= (GameScene::GetAllBandTipCount() * 6 / 10))
			{
				star->SetGeting(true);
			}
		}
		if (star->tags.SearchTag("3枚目"))
		{
			if (meterCount >= (GameScene::GetAllBandTipCount() * 9 / 10))
			{
				star->SetGeting(true);
			}
		}
	}
}

// CLEARロゴの描画処理
void ResultScene::ClearDraw()
{
	// バンドオブジェクトの探索
	auto bandPullLevels = GetInstance()->GetObjects<Band>();
	for (auto* bandPullLevel : bandPullLevels)
	{
		// バンドを引ききったら
		if ((int)(bandPullLevel->GetPullLevel() / -60.0f) >= tipCount)
		{				
			auto bandTips = GetInstance()->GetObjects<BandTip>();
			for (auto* bandTip : bandTips)
			{
				bandTip->SetVelo(0.0f, 0.0f, 0.0f);
			}
			// プレイヤー停止
			movePlayerFlag = false;
			
			// CLEARロゴの拡大描画中なら
			if (drawFlag == true)
			{
				ClearBig();
			}

			// CLEARロゴが拡大描画完了したら
			if (drawFlag == true &&
				drawClearFlag == true)
			{
				count += 1;
				
				// 1秒後(60frame)
				if (count >= 60)
				{
					drawFlag = false;	// 拡大描画処理終了
					moveFlag = true;	// CLEARロゴ移動処理開始
				}
			}

			// CLEARロゴが移動中なら
			if (moveFlag == true)
			{
				ClearMove();		// CLEARのロゴ縮小移動
			}
		}
	}
}

// CLEARのロゴ拡大表示
void ResultScene::ClearBig()
{
	auto object = GetInstance()->GetObjects<Quad>();
	for (auto& obj : object)
	{	
		// CLEARロゴの検索
		if (obj->tags.SearchTag("CLEAR"))
		{
			// 拡大出来たか？
			if(obj->GetScale().x < 850.0f &&
			   obj->GetScale().y < 250.0f)
			{
				// 拡大描画処理
				obj->SetScale((obj->GetScale().x + 14.0f),
							  (obj->GetScale().y + 4.0f),
							   0.0f);
			}
			else
			{
				// 拡大描画完了
				drawClearFlag = true;	
			}
		}
	}
}

// CLEARのロゴ縮小移動
void ResultScene::ClearMove()
{
	auto object = GetInstance()->GetObjects<Quad>();
	for (auto& obj : object)
	{
		// CLEARロゴの検索
		if (obj->tags.SearchTag("CLEAR"))
		{
			// 特定座標までにいなかったら
			if (obj->GetPos().x > -750.0f &&
				obj->GetPos().y < 440.0f)
			{
				// 移動処理
				obj->SetPos((obj->GetPos().x - 10.0f),
							(obj->GetPos().y + 6.0f),
							 0.0f);
			}
			// 特定サイズまでじゃなかったら
			if(obj->GetScale().x > 400.0f &&
			   obj->GetScale().y > 100.0f)
			{
				// 縮小処理
				obj->SetScale((obj->GetScale().x - 6.0f),
							  (obj->GetScale().y - 2.0f),
							   0.0f);
			}
			// 特定の条件に達したら
			if (obj->GetPos().x < -750.0f ||
				obj->GetPos().y > 440.0f ||
				obj->GetScale().x < 400.0f ||
				obj->GetScale().y < 100.0f)
			{
				// 移動処理完了
				moveFlag = false;
				uiFlag = true;
			}
		}
	}
}

// UI描画処理
void ResultScene::UI_Draw()
{
	if (layerFlag == false)
	{
		//「タイトルに戻る」のオブジェクト作成
		auto returnTitle = Object::Create<Quad>();
		returnTitle->SetTex("asset/Texture/Return_toTitle.png");	// 画像読み込み
		returnTitle->SetPos(700.0f, 0.0f, 0.0f);					// 座標を設定
		returnTitle->SetScale(420.0f, 150.0f, 0.0f);				// 大きさを設定
		returnTitle->tags.AddTag("UI");								// タグ付け
		returnTitle->layer = 1;										// レイヤーを設定

		//「ステージ選択に戻る」のオブジェクト作成
		auto returnHome = Object::Create<Quad>();
		returnHome->SetTex("asset/Texture/Return_toHome.png");		// 画像読み込み
		returnHome->SetPos(700.0f, -150.0f, 0.0f);					// 座標を設定
		returnHome->SetScale(420.0f, 150.0f, 0.0f);					// 大きさを設定
		returnHome->tags.AddTag("UI");								// タグ付け
		returnHome->layer = 1;										// レイヤーを設定

		//「リトライ」のオブジェクト作成
		auto retryLogo = Object::Create<Quad>();
		retryLogo->SetTex("asset/Texture/Retry.png");				// 画像読み込み
		retryLogo->SetPos(700.0f, -300.0f, 0.0f);					// 座標を設定
		retryLogo->SetScale(420.0f, 150.0f, 0.0f);					// 大きさを設定
		retryLogo->tags.AddTag("UI");								// タグ付け
		retryLogo->layer = 1;										// レイヤーを設定

		// フレームオブジェクト作成
		auto frame = Object::Create<Quad>();
		frame->SetTex("asset/Texture/Frame.png");					// 画像読み込み
		frame->SetPos(700.0f, 0.0f, 0.0f);							// 座標を設定
		frame->SetScale(420.0f, 150.0f, 0.0f);						// 大きさを設定
		frame->tags.AddTag("UI");									// タグ付け
		frame->tags.AddTag("frame");								// タグ付け
		frame->layer = 1;											// レイヤーを設定

		// レイヤー描画完了
		layerFlag = true;											
	}
}

// フレーム更新処理
void ResultScene::Frame_Update()
{
	// 遷移選択
	if (movePlayerFlag == false)
	{
		Frame_Input();				// フレーム移動入力処理
		Frame_Move();				// フレーム移動処理
	}
}

// フレーム移動入力処理
void ResultScene::Frame_Input()
{
	/*コントローラー:十字下キー
	 *キーボード　　:↓矢印キー
	 *どちらかが押されたら
	 */
	if ((input.GetButtonTrigger(XINPUT_DOWN) ||
		input.GetKeyTrigger(VK_DOWN)) &&
		GetFrameNum() < 3) {
		SetFrameNum(GetFrameNum() + 1);
	}
	/*コントローラー:十字上キー
	 *キーボード　　:↑矢印キー
	 *どちらかが押されたら
	 */
	if ((input.GetButtonTrigger(XINPUT_UP) ||
		input.GetKeyTrigger(VK_UP)) &&
		GetFrameNum() > 1) {
		SetFrameNum(GetFrameNum() - 1);
	}
}

// フレーム移動処理
void ResultScene::Frame_Move()
{
	// フレーム移動処理・入力後の各シーン遷移処理
	switch (GetFrameNum())
	{
	case 1: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(700.0f, 0.0f, 0.0f);
			}
		}
		// エンターキーorBボタンを押したら
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// 決定音
		}
		if (fadeOut_End == true)
		{
			//現在のシーンを「TitleScene」に切り替える
			SceneManager::ChangeScene(TITLE);
		}
		break; }
	case 2: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(700.0f, -150.0f, 0.0f);
			}
		}
		// エンターキーorBボタンを押したら
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// 決定音
		}
		if (fadeOut_End == true)
		{
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(HOME_1, 1);
		}
		break; }
	case 3: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(700.0f, -300.0f, 0.0f);
			}
		}
		// エンターキーorBボタンを押したら
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// 決定音
		}
		if (fadeOut_End == true)
		{
			int stageNum = (int)(GameOverScene::isEndSceneNum - SCENE_ENUM_OFFSET);
			//現在のシーンを直前にゲームオーバーした「GameScene」に切り替える
			SceneManager::ChangeScene(GameOverScene::isEndSceneNum, stageNum);
		}
		break; }
	default:
		break;
	}
}

// フェードイン処理		(明るくなる)
void ResultScene::Fade_In()
{
	auto Fade = GetInstance()->GetObjects<Quad>();
	for (auto& fade : Fade)
	{
		if (fade->tags.SearchTag("Fade"))
		{
			if (fade->GetColor().w >= 0.0f)
			{
				fade->SetColor(1.0f, 1.0f, 1.0f, fade->GetColor().w - 0.01f);
			}
		}
	}
}

// フェードアウト処理	(暗くなる)
void ResultScene::Fade_Out()
{
	auto Fade = GetInstance()->GetObjects<Quad>();
	for (auto& fade : Fade)
	{
		if (fade->tags.SearchTag("Fade"))
		{
			if (fade->GetColor().w <= 1.0f)
			{
				fade->SetColor(1.0f, 1.0f, 1.0f, fade->GetColor().w + 0.05f);
			}
			else
			{
				fadeOut_End = true;
			}
		}
	}
}