#include "GameScene.h"
#include "SceneManager.h"

GameScene::GameScene()
{
	bg.Init("asset/Texture/Beach.png");	// 背景を初期化
	bg.SetScale(1280.0f, 720.0f, 0.0f);	// 大きさを設定

	ground.resize(OBJECT_VALUE);
	for (int i = 0; i < OBJECT_VALUE; ++i)
	{
		ground[i] = new Ground;
		ground[i]->Init();	// 地面を描画
		ground[i]->SetPos(-620 + i * 50, -250.0f, 0.0f);	// 座標を初期化
	}
}

GameScene::~GameScene()
{
	bg.Uninit();	//背景を終了
	for (int i = 0; i < OBJECT_VALUE; ++i)
	{
		ground[i]->Uninit();
	}
}

void GameScene::Update()
{
	input.Update();	//キー入力の判定

	// "1"キーを押したら
	if (input.GetKeyTrigger(VK_1))
	{
		//現在のシーンを「ResultScene」に切り替える
		SceneManager::ChangeScene(SceneManager::TITLE);
	}

	// "3"キーを押したら
	if (input.GetKeyTrigger(VK_3))
	{
		//現在のシーンを「ResultScene」に切り替える
		SceneManager::ChangeScene(SceneManager::RESULT);
	}
}

void GameScene::Draw()
{
	bg.Draw();		// 背景を描画
	for (int i = 0; i < OBJECT_VALUE; ++i)
	{
		ground[i]->Draw();
	}
}
