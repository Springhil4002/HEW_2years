#include "TitleScene.h"
#include "SceneManager.h"
#include "Quad.h"

void TitleScene::Init()
{
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// サウンド停止
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM005);	// サウンド停止
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM001);	// サウンド再生
	
	// オブジェクト作成
	auto bg				= Object::Create<Quad>();			// 背景
	auto titleLogo		= Object::Create<Quad>();			// タイトルロゴ
	auto gameStart		= Object::Create<Quad>();			// ゲームスタートのアイコン
	auto playOperate	= Object::Create<Quad>();			// 遊び方のアイコン
	auto frame			= Object::Create<Quad>();			// アイコンを囲むフレーム
	auto fade			= Object::Create<Quad>();			// フェードイン・フェードアウト用
				
	bg->SetTex("asset/Texture/Title_bg.jpg");				// 画像読み込み
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);			// 大きさを設定
	bg->layer = -1;											// レイヤー設定

	titleLogo->SetTex("asset/Texture/Title_Logo.jpg");		// 画像読み込み
	titleLogo->SetPos(0.0f, 200.0f, 0.0f);					// 座標を設定
	titleLogo->SetScale(1000.0f, 600.0f, 0.0f);				// 大きさを設定

	gameStart->SetTex("asset/Texture/Start_Logo.png");		// 画像読み込み
	gameStart->SetPos(0.0f, -200.0f, 0.0f);					// 座標を設定
	gameStart->SetScale(600.0f, 200.0f, 0.0f);				// 大きさを設定

	playOperate->SetTex("asset/Texture/How_to_play.png");	// 画像読み込み
	playOperate->SetPos(0.0f, -400.0f, 0.0f);				// 座標を設定
	playOperate->SetScale(400.0f, 150.0f, 0.0f);			// 大きさを設定

	frame->SetTex("asset/Texture/Frame.png");				// 画像読み込み
	frame->SetPos(0.0f, -200.0f, 0.0f);						// 座標を設定
	frame->SetScale(600.0f, 200.0f, 0.0f);					// 大きさを設定
	frame->tags.AddTag("frame");							// タグ付け

	fade->SetTex("asset/Texture/Fade_Black.png",			// 画像読み込み
			1,1,0,0,	1.0f,1.0f,1.0f,1.0f);								
	fade->SetPos(0.0f, 0.0f, 0.0f);							// 座標設定
	fade->SetScale(1920.0f, 1080.0f, 0.0f);					// 大きさを設定
	fade->tags.AddTag("Fade");								// タグ付け
	fade->layer = 2;										// レイヤーを設定
}

void TitleScene::Update()
{
	Fade_In();		// フェードイン処理		(明るくなる)
	
	Frame_Input();	// フレーム移動入力処理
	Frame_Move();	// フレームの移動処理
	if (fadeOut_Start == true)
	{
		Fade_Out();	// フェードアウト処理	(暗くなる)
	}

	auto objects = objectInstance;
	for (auto& obj : objects)
	{
		obj->Update();
	}
}

// フレーム移動入力処理
void TitleScene::Frame_Input()
{
	/* コントローラー :十字下キー
	 *  キーボード   :↓矢印キー
	 *  どちらかが押されたら
	 */
	if((input.GetButtonTrigger(XINPUT_DOWN) ||
		input.GetKeyTrigger	  (VK_DOWN)) &&
		GetFrameNum() < 2) {
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE003);	// 選択音
		SetFrameNum(GetFrameNum() + 1);
	}
	/* コントローラー :十字上キー
	 *  キーボード   :↑矢印キー
	 *  どちらかが押されたら
	 */
	if((input.GetButtonTrigger(XINPUT_UP) ||
		input.GetKeyTrigger	  (VK_UP)) &&
		GetFrameNum() > 1) {
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE003);	// 選択音
		SetFrameNum(GetFrameNum() - 1);
	}
}

// フレームの移動処理
void TitleScene::Frame_Move()
{
	switch (GetFrameNum())
	{
	case 1: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(0.0f, -200.0f, 0.0f);				// 座標を設定
				quad->SetScale(600.0f, 200.0f, 0.0f);			// 大きさを設定
			}
		}
		// エンターキーorBボタンを押したら
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE001);	// 決定音
		}
		// 暗くなりきると遷移する
		if (fadeOut_End == true)
		{
			//現在のシーンを「HomeScene」に切り替える
			SceneManager::ChangeScene(HOME_1, 1);
		}
		break; }
	case 2: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(0.0f, -400.0f, 0.0f);				// 座標を設定
				quad->SetScale(400.0f, 150.0f, 0.0f);			// 大きさを設定
			}
		}
		// エンターキーorBボタンを押したら
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// 決定音
		}
		// 暗くなりきると遷移する
		if (fadeOut_End == true)
		{
			//現在のシーンを「PlayOperateScene」に切り替える
			SceneManager::ChangeScene(PLAYOPERATE);
		}
		break; }
	default:
		break;
	}
}

// フェードイン処理		(明るくなる)
void TitleScene::Fade_In()
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
void TitleScene::Fade_Out()
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