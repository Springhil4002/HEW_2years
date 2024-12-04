#include "GameScene.h"
#include "SceneManager.h"

GameScene::GameScene()
{
	bg.Init("asset/Texture/Beach.png");	// 背景を初期化
	bg.SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);	// 大きさを設定

	const float playerX = GROUND_OFFSET_X + 20.0f;
	const float playerY = GROUND_OFFSET_Y + (1.5*BLOCK_SIZE);

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

	test.Init("asset/Texture/player.png");
	test.SetPos(playerX, playerY, 0.0f);	// 座標を設定
	test.SetScale(BLOCK_SIZE, 2 * BLOCK_SIZE, 0.0f);	// 大きさを設定
	test.SetAcce(0, -1, 0);
	test.SetVelo(1, 20, 0);


	Object* buf[2];
	buf[0] = new Entity;
	buf[1] = new Entity;
	Object::GetInstance()->push_back(buf[0]);
	Object::GetInstance()->push_back(buf[1]);
	for (auto& ent : Object::GetObj<Entity>())
	{
		ent->Init("asset/Texture/explotion.png");
		ent->SetScale(60, 60, 0);
	}
	Object::GetObj<Entity>()[0]->SetPos(playerX, playerY, 0.0f);	// 座標を設定
	Object::GetObj<Entity>()[0]->SetVelo(1, 0, 0);	// を設定
	Object::GetObj<Entity>()[1]->SetPos(playerX + 120, playerY, 0.0f);	// 座標を設定



}

GameScene::~GameScene()
{
	bg.Uninit();		// 背景を終了
	player.Uninit();	// プレイヤーを終了
	for (int i = 0; i < OBJECT_X_VALUE; ++i)
	{
		ground[i]->Uninit();
	}
	test.Uninit();
	for (auto& ent : Object::GetObj<Entity>())
	{
		ent->Uninit();
	}
}

void GameScene::Update()
{
	input.Update();	//キー入力の判定

	player.Update();

	test.Update();

	for (auto& ent : Object::GetObj<Entity>())
	{
		ent->Update();
	}


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
	test.Draw();

	for (auto& ent : Object::GetObj<Entity>())
	{
		ent->Draw();
	}
}
