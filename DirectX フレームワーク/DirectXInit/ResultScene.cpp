#include "ResultScene.h"
#include "SceneManager.h"
#include "GameScene.h"
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
	//std::cout << "bandTipCount:" << _num << std::endl;
	tipCount = _num;
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM003);	// サウンドを停止
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM005);	// サウンドを再生

	// 背景オブジェクトの作成
	auto bg = Object::Create<Quad>();
	bg->SetTex("asset/Texture/Night.jpg");
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
	bg->layer = -1;

	// プレイヤーオブジェクトの作成
	auto player = Object::Create<Player>();
	player->SetPos(-800.0f, -400.0f, 0.0f);

	// CLEARのロゴオブジェクトの作成
	auto clear_Logo = Object::Create<Quad>();
	clear_Logo->SetTex("asset/Texture/Clear_Logo.png");
	clear_Logo->SetPos(0.0f, 0.0f, 0.0f);
	clear_Logo->SetScale(0.0f, 0.0f, 0.0f);
	clear_Logo->tags.AddTag("CLEAR");
	clear_Logo->layer = 2;

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
	band->SetPos(30.0f, -420.0f, 0.0f);
	band->SetScale(BLOCK_SIZE, BLOCK_SIZE, 0.0f);
	band->layer = 1;
	band->SetLength(tipCount+1);

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
	// 引っ張った長さに応じてスコアを更新
	PullScoreUpdate();

	// コイン獲得数UIの各桁更新処理
	CoinCounter();

	// コイン獲得数の割合に応じてStarTipの獲得状況の更新
	CoinGetPercent();

	// CLEARロゴの拡大表示と表示後の移動
	ClearDraw();

	auto objects = objectInstance;
	for (auto& obj : objects)
	{
		obj->Update();
	}

	// Bボタンorエンターキーを押したら
	if (input.GetButtonTrigger(XINPUT_B) || 
		input.GetKeyTrigger(VK_RETURN))
	{
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
		//現在のシーンを「TitleScene」に切り替える
		SceneManager::ChangeScene(TITLE);
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
				ClearMove();
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
				obj->SetScale((obj->GetScale().x + 7.0f),
							  (obj->GetScale().y + 2.0f),
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
				obj->SetPos((obj->GetPos().x - 5.0f),
							(obj->GetPos().y + 3.0f),
							 0.0f);
			}
			// 特定サイズまでじゃなかったら
			if(obj->GetScale().x > 400.0f &&
			   obj->GetScale().y > 100.0f)
			{
				// 縮小処理
				obj->SetScale((obj->GetScale().x - 3.0f),
							  (obj->GetScale().y - 1.0f),
							   0.0f);
			}
			// 特定の条件に達したら
			if (obj->GetPos().x < -750.0f &&
				obj->GetPos().y > 440.0f &&
				obj->GetScale().x < 400.0f &&
				obj->GetScale().y < 100.0f)
			{
				// 移動処理完了
				moveFlag = false;
			}
		}
	}
}
