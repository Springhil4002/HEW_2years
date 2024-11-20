#include "TitleScene.h"
#include "SceneManager.h"

TitleScene::TitleScene()
{
	bg.Init("asset/Texture/Future.jpg");	//背景を初期化
	bg.SetScale(1280.0f, 720.0f, 0.0f);		//大きさを設定

	// 配列の要素にオブジェクトを追加
	objects.emplace_back(new Ground);

	// オブジェクト初期化
	for (auto& o : objects) {
		o->Init();
	}
}

TitleScene::~TitleScene()
{
	bg.Uninit();	// 背景を終了
	
	// オブジェクト終了処理
	for (auto& o : objects) {
		o->Uninit();
	}
}

void TitleScene::Update()
{
	input.Update();	//キー入力の判定
	
	// オブジェクト更新
	for (auto& o : objects) {
		o->Update();
	}

	// "2"キーを押したら
	if (input.GetKeyTrigger(VK_2))
	{
		//現在のシーンを「GameScene」に切り替える
		SceneManager::ChangeScene(SceneManager::GAME);
	}

	// "3"キーを押したら
	if (input.GetKeyTrigger(VK_3))
	{
		//現在のシーンを「GameScene」に切り替える
		SceneManager::ChangeScene(SceneManager::RESULT);
	}
}

void TitleScene::Draw()
{
	bg.Draw();		// 背景を描画
	//ground.Draw();	// 地面を描画
	
	// オブジェクト描画
	for (auto& o : objects) {
		o->Draw();
	}
}