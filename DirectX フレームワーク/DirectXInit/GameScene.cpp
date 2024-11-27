#include "GameScene.h"
#include "SceneManager.h"

GameScene::GameScene()
{
	bg.Init("asset/Texture/Beach.png");	// 背景を初期化
	bg.SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);	// 大きさを設定

	const float playerX = GROUND_OFFSET_X + 20.0f;
	const float playerY = GROUND_OFFSET_Y + (2 * BLOCK_SIZE);

	player.Init("asset/Texture/player.png");// プレイヤーを初期化
	player.SetPos(playerX, playerY, 0.0f);	// 座標を設定
	player.SetScale(BLOCK_SIZE, 2*BLOCK_SIZE, 0.0f);	// 大きさを設定

	ground.resize(OBJECT_X_VALUE);
	for (int i = 0; i < OBJECT_X_VALUE; ++i)
	{
		ground[i] = new Ground;
		ground[i]->Init();	// 地面を描画
		ground[i]->SetPos(GROUND_OFFSET_X + i * BLOCK_SIZE, GROUND_OFFSET_Y, 0.0f);	// 座標を初期化
	}
}

GameScene::~GameScene()
{
	bg.Uninit();		// 背景を終了
	player.Uninit();	// プレイヤーを終了
	for (int i = 0; i < OBJECT_X_VALUE; ++i)
	{
		ground[i]->Uninit();
	}
}

void GameScene::Update()
{
	input.Update();	//キー入力の判定

	player.Update();

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
	player.Draw();	// プレイヤーを描画
	for (int i = 0; i < OBJECT_X_VALUE; ++i)
	{
		ground[i]->Draw();
	}
}
