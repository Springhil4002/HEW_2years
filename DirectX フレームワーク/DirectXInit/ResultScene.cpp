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

void ResultScene::Init(int _num)
{
	//std::cout << "bandTipCount:" << _num << std::endl;
	tipCount = _num;
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM003);	// サウンドを停止
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM005);	// サウンドを再生

	auto bg = Object::Create<Quad>();
	
	bg->SetTex("asset/Texture/Night.jpg");
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
	bg->layer = -1;

	auto player = Object::Create<Player>();
	player->layer = 1;

	const int stage[18][64] = {
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};


	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			switch (stage[j][i])
			{
			case 1:
				auto ground = Object::Create<Ground>();
				ground->SetPos(-1890.0f + i * BLOCK_SIZE, -(-510.0f + j * BLOCK_SIZE), 0.0f);	// 座標を初期化

				if (47<=i && i<=(47+tipCount))
				{
					ground->tags.AddTag("BandA");
				}
				break;
			}
		}
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
	coinNum1->SetPos(200.0f, 0.0f, 0.0f);
	coinNum10->SetPos(0.0f, 0.0f, 0.0f);
	coinNum100->SetPos(-200.0f, 0.0f, 0.0f);

	// コイン獲得数の拡大表示
	coinNum1->SetScale(200.0f, 400.0f, 0.0f);
	coinNum10->SetScale(200.0f, 400.0f, 0.0f);
	coinNum100->SetScale(200.0f, 400.0f, 0.0f);

	// コイン獲得数オブジェクトのタグ付け
	coinNum1->tags.AddTag("一の位");
	coinNum10->tags.AddTag("十の位");
	coinNum100->tags.AddTag("百の位");

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
		if (obj->tags.SearchTag("BandA"))
		{
			band->Add(obj);
		}
	}

	for (auto& obj : objectInstance)
	{
		obj->Init();
	}
}

void ResultScene::Update()
{
	// 引っ張った長さに応じてスコアを更新
	auto bandPullLevels = GetInstance()->GetObjects<Band>();
	for (auto& bandPullLevel : bandPullLevels)
	{
		meterCount = (int)(bandPullLevel->GetPullLevel() / -60.0f);
	}

	// コイン獲得数UIの各桁更新処理
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

	// コイン獲得数の割合に応じてStarTipの獲得状況の更新
	auto star_s = GetInstance()->GetObjects<StarTip>();
	for (auto& star : star_s)
	{
		if (star->tags.SearchTag("1枚目"))
		{
			if (meterCount >=(GameScene::GetAllBandTipCount()*3/10))
			{
				star->SetGeting(true);
			}
		}
		if (star->tags.SearchTag("2枚目"))
		{
			if (meterCount >= (GameScene::GetAllBandTipCount()*3/5))
			{
				star->SetGeting(true);
			}
		}
		if (star->tags.SearchTag("3枚目"))
		{
			if (meterCount >= (GameScene::GetAllBandTipCount()*9/10))
			{
				star->SetGeting(true);
			}
		}
	}

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

	auto players = GetInstance()->GetObjects<Player>();
	for (auto& player : players)
	{
		if (-510.0f > player->GetPos().y + 120.0f)
		{
			SceneManager::ChangeScene(TITLE);
		}
	}
}