#include "PlayOperateScene.h"
#include "SceneManager.h"
#include "Quad.h"
#include "Application.h"

void PlayOperateScene::Init()
{
	auto bg				= Object::Create<Quad>();			// 背景
	auto keyPad			= Object::Create<Quad>();			// 操作方法
	auto close			= Object::Create<Quad>();			// 閉じるアイコン
	auto frame			= Object::Create<Quad>();			// アイコンを囲むフレーム
	auto fade			= Object::Create<Quad>();			// フェードイン・フェードアウト用

	bg->SetTex("asset/Texture/Bg.png");						// 画像読み込み
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);			// 大きさを設定
	bg->layer = -1;											// レイヤーを設定

	keyPad->SetTex("asset/Texture/KeyPad.png");				// 画像読み込み
	keyPad->SetPos(0.0f, 100.0f, 0.0f);						// 座標を設定
	keyPad->SetScale(1000.0f, 800.0f, 0.0f);				// 大きさを設定

	close->SetTex("asset/Texture/Close.png");				// 画像読み込み
	close->SetPos(0.0f, -400.0f, 0.0f);						// 座標を設定
	close->SetScale(300.0f, 150.0f, 0.0f);					// 大きさを設定

	frame->SetTex("asset/Texture/Frame.png");				// 画像読み込み
	frame->SetPos(0.0f, -400.0f, 0.0f);						// 座標を設定
	frame->SetScale(300.0f, 150.0f, 0.0f);					// 大きさを設定
	frame->tags.AddTag("frame");							// タグ付け

	// フェードイン・フェードアウト
	fade->SetTex("asset/Texture/Fade.png");						// 画像読み込み
	fade->SetPos(0.0f, 0.0f, 0.0f);								// 座標設定
	fade->SetScale(1920.0f, 1080.0f, 0.0f);						// 大きさを設定
	fade->tags.AddTag("Fade");									// タグ付け
	fade->layer = 10;											// レイヤーを設定
}

void PlayOperateScene::Update()
{
	if (fade_In == true)
	{
		Fade_In();			// フェードイン処理		(明るくなる)
	}
	
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
	if (Application::GetFpsCounter() % 6 == 0)
	{
		countFadeIn += 1;
		auto Fade = GetInstance()->GetObjects<Quad>();
		for (auto& fade : Fade)
		{
			if (fade->tags.SearchTag("Fade"))
			{
				switch (countFadeIn)
				{
				case 1: {
					fade->SetTex("asset/Texture/Fade/Fade_In_1.png");	// 画像読み込み
					break; }
				case 2: {
					fade->SetTex("asset/Texture/Fade/Fade_In_2.png");	// 画像読み込み
					break; }
				case 3: {
					fade->SetTex("asset/Texture/Fade/Fade_In_3.png");	// 画像読み込み
					break; }
				case 4: {
					fade->SetTex("asset/Texture/Fade/Fade_In_4.png");	// 画像読み込み
					break; }
				case 5: {
					fade->SetTex("asset/Texture/Fade/Fade_In_5.png");	// 画像読み込み
					break; }
				case 6: {
					fade->SetTex("asset/Texture/Fade/Fade_In_6.png");	// 画像読み込み
					break; }
				case 7: {
					fade->SetTex("asset/Texture/Fade/Fade_In_7.png");	// 画像読み込み
					break; }
				case 8: {
					fade->SetTex("asset/Texture/Fade/Fade_In_8.png");	// 画像読み込み
					break; }
				case 9: {
					fade->SetTex("asset/Texture/Fade/Fade_In_9.png");	// 画像読み込み
					break; }
				case 10: {
					fade->SetTex("asset/Texture/Fade/Fade_In_10.png");	// 画像読み込み
					break; }
				default: {
					fade->SetColor(1.0f, 1.0f, 1.0f, 0.0f);
					fade->SetTex("asset/Texture/Fade.png");		// 画像読み込み
					fade_In = false;							// フェードイン終了
					break; }
				}
			}
		}
	}
}

// フェードアウト処理	(暗くなる)
void PlayOperateScene::Fade_Out()
{
	if (Application::GetFpsCounter() % 6 == 0)
	{
		countFadeOut += 1;
		auto Fade = GetInstance()->GetObjects<Quad>();
		for (auto& fade : Fade)
		{
			if (fade->tags.SearchTag("Fade"))
			{
				fade->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
				switch (countFadeOut)
				{
				case 1: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_1.png");	// 画像読み込み
					break; }
				case 2: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_2.png");	// 画像読み込み
					break; }
				case 3: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_3.png");	// 画像読み込み
					break; }
				case 4: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_4.png");	// 画像読み込み
					break; }
				case 5: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_5.png");	// 画像読み込み
					break; }
				case 6: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_6.png");	// 画像読み込み
					break; }
				case 7: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_7.png");	// 画像読み込み
					break; }
				case 8: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_8.png");	// 画像読み込み
					break; }
				case 9: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_9.png");	// 画像読み込み
					break; }
				case 10: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_10.png");	// 画像読み込み
					break; }
				default: {
					fade->SetTex("asset/Texture/Fade.png");		// 画像読み込み
					fadeOut_End = true;
					break; }
				}
			}
		}
	}
}