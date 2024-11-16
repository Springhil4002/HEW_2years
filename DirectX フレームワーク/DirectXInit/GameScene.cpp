#include "GameScene.h"
#include "SceneManager.h"

GameScene::GameScene()
{
	BackGround.Init("asset/Texture/Beach.png");			//背景を初期化
	BackGround.SetScale(1280.0f, 720.0f, 0.0f);	//大きさを設定
}

GameScene::~GameScene()
{
	BackGround.Uninit();	//背景を終了
}

void GameScene::Update()
{
	input.Update();	//キー入力の判定
	//エンターキーを押したら
	if (input.GetKeyTrigger(VK_3))
	{
		//現在のシーンを「ResultScene」に切り替える
		SceneManager::ChangeScene(SceneManager::RESULT);
	}
}

void GameScene::Draw()
{
	BackGround.Draw();		//背景を描画
}


