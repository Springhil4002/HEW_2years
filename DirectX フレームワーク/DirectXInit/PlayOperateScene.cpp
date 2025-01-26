#include "PlayOperateScene.h"
#include "SceneManager.h"
#include "Quad.h"

void PlayOperateScene::Init()
{
	auto bg				= Object::Create<Quad>();			// 背景
	auto keyPad			= Object::Create<Quad>();			// 操作方法
	auto close			= Object::Create<Quad>();			// 閉じるアイコン
	auto frame			= Object::Create<Quad>();			// アイコンを囲むフレーム

	bg->SetTex("asset/Texture/PlayOperate_bg.jpg");			// 画像読み込み
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);			// 大きさを設定
	bg->layer = -1;											// レイヤーを設定

	keyPad->SetTex("asset/Texture/KeyPad.png");				// 画像読み込み
	keyPad->SetPos(0.0f, 100.0f, 0.0f);						// 座標を設定
	keyPad->SetScale(1000.0f, 800.0f, 0.0f);				// 大きさを設定

	close->SetTex("asset/Texture/Close.png");				// 画像読み込み
	close->SetPos(0.0f, -400.0f, 0.0f);						// 座標を設定
	close->SetScale(200.0f, 100.0f, 0.0f);					// 大きさを設定

	frame->SetTex("asset/Texture/Frame.png");				// 画像読み込み
	frame->SetPos(0.0f, -400.0f, 0.0f);						// 座標を設定
	frame->SetScale(200.0f, 100.0f, 0.0f);					// 大きさを設定
	frame->tags.AddTag("frame");							// タグ付け
}

void PlayOperateScene::Update()
{
	// エンターキーorBボタンを押したら
	if (input.GetKeyTrigger(VK_RETURN) ||
		input.GetButtonTrigger(XINPUT_B))
	{
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
		//現在のシーンを「TitleScene」に切り替える
		SceneManager::ChangeScene(TITLE);
	}
}
