#include "ResultScene.h"
#include "SceneManager.h"

ResultScene::ResultScene()
{
	bg.Init("asset/Texture/Night.jpg");		//背景を初期化
	bg.SetScale(1280.0f, 720.0f, 0.0f);	//大きさを設定
}

ResultScene::~ResultScene()
{
	bg.Uninit();	//背景を終了
}

void ResultScene::Update()
{
	input.Update();	//キー入力の判定
	// "1"キーを押したら
	if (input.GetKeyTrigger(VK_1))
	{
		//現在のシーンを「TitleScene」に切り替える
		SceneManager::ChangeScene(SceneManager::TITLE);
	}

	// "2"キーを押したら
	if (input.GetKeyTrigger(VK_2))
	{
		//現在のシーンを「TitleScene」に切り替える
		SceneManager::ChangeScene(SceneManager::GAME);
	}
}

void ResultScene::Draw()
{
	bg.Draw();		//背景を描画
}
