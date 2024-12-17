#include "TitleScene.h"
#include "SceneManager.h"
#include "Quad.h"

TitleScene::TitleScene()
{
	//bg.Init("asset/Texture/Future.jpg");	//背景を初期化
	//bg.SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);		//大きさを設定
}

TitleScene::~TitleScene()
{
	//bg.Uninit();	// 背景を終了
}

void TitleScene::Init()
{
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM003);	// サウンド停止
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM001);	// サウンド再生
	auto bg = Object::Create<Quad>();
	bg->SetTex("asset/Texture/Future.jpg");
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);		//大きさを設定
}

void TitleScene::Update()
{
	//input.Update();	//キー入力の判定
	
	// "2"キーを押したら
	if (input.GetKeyTrigger(VK_2))
	{
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
		//現在のシーンを「GameScene」に切り替える
		SceneManager::ChangeScene(SceneManager::GAME);
	}
}

//void TitleScene::Draw()
//{
//	bg.Draw();		// 背景を描画
//}