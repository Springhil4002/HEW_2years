#include "PlayOperateScene.h"
#include "SceneManager.h"
#include "Quad.h"

void PlayOperateScene::Init()
{
	auto bg				= Object::Create<Quad>();			// 背景
	auto keyPad			= Object::Create<Quad>();			// 操作方法
	auto close			= Object::Create<Quad>();			// 閉じるアイコン
	auto frame			= Object::Create<Quad>();			// アイコンを囲むフレーム
	auto fade			= Object::Create<Quad>();			// フェードイン・フェードアウト用

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

	fade->SetTex("asset/Texture/Fade_Black.png",			// 画像読み込み
		1, 1, 0, 0, 1.0f, 1.0f, 1.0f, 1.0f);
	fade->SetPos(0.0f, 0.0f, 0.0f);							// 座標設定
	fade->SetScale(1920.0f, 1080.0f, 0.0f);					// 大きさを設定
	fade->tags.AddTag("Fade");								// タグ付け
	fade->layer = 2;										// レイヤーを設定
}

void PlayOperateScene::Update()
{
	Fade_In();				// フェードイン処理		(明るくなる)

	Back_ToTitle();			// タイトルに戻る
	if (fadeOut_Start == true)
	{
		Fade_Out();			// フェードアウト処理	(暗くなる)
	}
	
	auto objects = objectInstance;
	for (auto& obj : objects)
	{
		obj->Update();
	}
}

// タイトルに戻る
void PlayOperateScene::Back_ToTitle()
{
	// エンターキーorBボタンorAボタンを押したら
	if (input.GetKeyTrigger(VK_RETURN) ||
		input.GetButtonTrigger(XINPUT_B) ||
		input.GetButtonTrigger(XINPUT_A))
	{
		fadeOut_Start = true;
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
	}
	// 暗くなりきると遷移する
	if (fadeOut_End == true)
	{
		//現在のシーンを「TitleScene」に切り替える
		SceneManager::ChangeScene(TITLE);
	}
}

// フェードイン処理		(明るくなる)
void PlayOperateScene::Fade_In()
{
	auto Fade = GetInstance()->GetObjects<Quad>();
	for (auto& fade : Fade)
	{
		if (fade->tags.SearchTag("Fade"))
		{
			if (fade->GetColor().w >= 0.0f)
			{
				fade->SetColor(1.0f, 1.0f, 1.0f, fade->GetColor().w - 0.01f);
			}
		}
	}
}

// フェードアウト処理	(暗くなる)
void PlayOperateScene::Fade_Out()
{
	auto Fade = GetInstance()->GetObjects<Quad>();
	for (auto& fade : Fade)
	{
		if (fade->tags.SearchTag("Fade"))
		{
			if (fade->GetColor().w <= 1.0f)
			{
				fade->SetColor(1.0f, 1.0f, 1.0f, fade->GetColor().w + 0.05f);
			}
			else
			{
				fadeOut_End = true;
			}
		}
	}
}