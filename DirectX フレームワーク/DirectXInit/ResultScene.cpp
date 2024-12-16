#include "ResultScene.h"
#include "SceneManager.h"
#include "Quad.h"

ResultScene::ResultScene()
{
	//bg.Init("asset/Texture/Night.jpg");		//背景を初期化
	//bg.SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);	//大きさを設定
}

ResultScene::~ResultScene()
{
	SceneManager::m_SoundManager.Uninit();	// サウンドマネージャーを終了
	//bg.Uninit();	//背景を終了
}

void ResultScene::Init()
{
	auto bg = Object::Create<Quad>();
	bg->SetTex("asset/Texture/Night.jpg");
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
}

void ResultScene::Update()
{
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// サウンドを再生
	//input.Update();	//キー入力の判定
	// "1"キーを押したら
	if (input.GetKeyTrigger(VK_1))
	{
		//現在のシーンを「TitleScene」に切り替える
		SceneManager::ChangeScene(SceneManager::TITLE);
	}
}

//void ResultScene::Draw()
//{
//	bg.Draw();		//背景を描画
//}
