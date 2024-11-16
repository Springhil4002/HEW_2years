#include "TitleScene.h"
#include "SceneManager.h"

TitleScene::TitleScene()
{
	BackGround.Init("asset/Texture/Future.jpg");	//背景を初期化
	BackGround.SetScale(1280.0f, 720.0f, 0.0f);		//大きさを設定
}

TitleScene::~TitleScene()
{
	BackGround.Uninit();	//背景を終了
}

void TitleScene::Update()
{
	input.Update();	//キー入力の判定
	//エンターキーを押したら
	if (input.GetKeyTrigger(VK_2))
	{
		//現在のシーンを「GameScene」に切り替える
		SceneManager::ChangeScene(SceneManager::GAME);
	}
}

void TitleScene::Draw()
{
	BackGround.Draw();		//背景を描画
}


