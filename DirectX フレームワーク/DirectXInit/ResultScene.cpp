#include "ResultScene.h"
#include "SceneManager.h"

ResultScene::ResultScene()
{
	BackGround.Init("asset/Texture/Night.jpg");		//背景を初期化
	BackGround.SetScale(1280.0f, 720.0f, 0.0f);	//大きさを設定
}

ResultScene::~ResultScene()
{
	BackGround.Uninit();	//背景を終了
}

void ResultScene::Update()
{
	input.Update();	//キー入力の判定
	//エンターキーを押したら
	if (input.GetKeyTrigger(VK_1))
	{
		//現在のシーンを「TitleScene」に切り替える
		SceneManager::ChangeScene(SceneManager::TITLE);
	}
}

void ResultScene::Draw()
{
	BackGround.Draw();		//背景を描画
}
