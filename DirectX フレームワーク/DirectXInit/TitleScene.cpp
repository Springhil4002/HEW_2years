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
	auto buttonLogo = Object::Create<Quad>();
	auto titleLogo = Object::Create<Quad>();
	bg->SetTex("asset/Texture/Future.jpg");
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);			//大きさを設定
	buttonLogo->SetTex("asset/Texture/Start_Logo.png");
	buttonLogo->SetPos(0.0f, -300.0f, 0.0f);				//座標を設定
	buttonLogo->SetScale(600.0f, 200.0f, 0.0f);				//大きさを設定
	titleLogo->SetTex("asset/Texture/Title_Logo.png");		
	titleLogo->SetPos(0.0f, 200.0f, 0.0f);					//座標を設定
	titleLogo->SetScale(800.0f, 350.0f, 0.0f);				//大きさを設定
}

void TitleScene::Update()
{
	// エンターキーorBボタンを押したら
	if (input.GetKeyTrigger(VK_RETURN)||
		input.GetButtonTrigger(XINPUT_B))
	{
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
		//現在のシーンを「GameScene」に切り替える
		SceneManager::ChangeScene(SceneManager::HOME_1);
	}
}

//void TitleScene::Draw()
//{
//	bg.Draw();		// 背景を描画
//}