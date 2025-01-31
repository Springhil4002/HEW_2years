#include "TitleScene.h"
#include "SceneManager.h"
#include "Quad.h"
#include "Application.h"

void TitleScene::Init()
{
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// サウンド停止
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// サウンド停止
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM005);	// サウンド停止
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM001);	// サウンド再生
	
	// オブジェクト作成
	auto bg				= Object::Create<Quad>();			// 背景
	auto titleLogo		= Object::Create<Quad>();			// タイトルロゴ
	auto gameStart		= Object::Create<Quad>();			// ゲームスタートのアイコン
	auto playOperate	= Object::Create<Quad>();			// 遊び方のアイコン
	auto frame			= Object::Create<Quad>();			// アイコンを囲むフレーム
	// フェードイン・フェードアウト
	auto fade = Object::Create<Quad>();
	fade->SetTex("asset/Texture/Fade.png");						// 画像読み込み
	fade->SetPos(0.0f, 0.0f, 0.0f);								// 座標設定
	fade->SetScale(1920.0f, 1080.0f, 0.0f);						// 大きさを設定
	fade->tags.AddTag("Fade");									// タグ付け
	fade->layer = 10;											// レイヤーを設定

	Quad* fade_move[20];
	for (int i = 0; i < 20; i++)
	{
		fade_move[i] = Object::Create<Quad>();
		fade_move[i]->layer = -10;
	}
	for (int i = 0; i < 20; i++)
	{
		switch (i)
		{
		case 0:
			fade_move[i]->SetTex("asset/Texture/Fade/Fade_In_1.png");		// 画像読み込み
			break;
		case 1:
			fade_move[i]->SetTex("asset/Texture/Fade/Fade_In_2.png");		// 画像読み込み
			break;
		case 2:
			fade_move[i]->SetTex("asset/Texture/Fade/Fade_In_3.png");		// 画像読み込み
			break;
		case 3:
			fade_move[3]->SetTex("asset/Texture/Fade/Fade_In_4.png");		// 画像読み込み
			break;
		case 4:
			fade_move[4]->SetTex("asset/Texture/Fade/Fade_In_5.png");		// 画像読み込み
			break;
		case 5:
			fade_move[5]->SetTex("asset/Texture/Fade/Fade_In_6.png");		// 画像読み込み
			break;
		case 6:
			fade_move[6]->SetTex("asset/Texture/Fade/Fade_In_7.png");		// 画像読み込み
			break;
		case 7:
			fade_move[7]->SetTex("asset/Texture/Fade/Fade_In_8.png");		// 画像読み込み
			break;
		case 8:
			fade_move[8]->SetTex("asset/Texture/Fade/Fade_In_9.png");		// 画像読み込み
			break;
		case 9:
			fade_move[9]->SetTex("asset/Texture/Fade/Fade_In_10.png");		// 画像読み込み
			break;
		case 10:
			fade_move[10]->SetTex("asset/Texture/Fade/Fade_Out_1.png");		// 画像読み込み
			break;
		case 11:
			fade_move[11]->SetTex("asset/Texture/Fade/Fade_Out_2.png");		// 画像読み込み
			break;
		case 12:
			fade_move[12]->SetTex("asset/Texture/Fade/Fade_Out_3.png");		// 画像読み込み
			break;
		case 13:
			fade_move[13]->SetTex("asset/Texture/Fade/Fade_Out_4.png");		// 画像読み込み
			break;
		case 14:
			fade_move[14]->SetTex("asset/Texture/Fade/Fade_Out_5.png");		// 画像読み込み
			break;
		case 15:
			fade_move[15]->SetTex("asset/Texture/Fade/Fade_Out_6.png");		// 画像読み込み
			break;
		case 16:
			fade_move[16]->SetTex("asset/Texture/Fade/Fade_Out_7.png");		// 画像読み込み
			break;
		case 17:
			fade_move[17]->SetTex("asset/Texture/Fade/Fade_Out_8.png");		// 画像読み込み
			break;
		case 18:
			fade_move[18]->SetTex("asset/Texture/Fade/Fade_Out_9.png");		// 画像読み込み	
			break;
		case 19:
			fade_move[19]->SetTex("asset/Texture/Fade/Fade_Out_10.png");	// 画像読み込み
			break;
		}
	}
				
	bg->SetTex("asset/Texture/Bg.png");						// 画像読み込み
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);			// 大きさを設定
	bg->layer = -1;											// レイヤー設定

	titleLogo->SetTex("asset/Texture/Title_Logo.png");		// 画像読み込み
	titleLogo->SetPos(0.0f, 200.0f, 0.0f);					// 座標を設定
	titleLogo->SetScale(1200.0f, 600.0f, 0.0f);				// 大きさを設定

	gameStart->SetTex("asset/Texture/Start_Logo.png");		// 画像読み込み
	gameStart->SetPos(0.0f, -200.0f, 0.0f);					// 座標を設定
	gameStart->SetScale(800.0f, 180.0f, 0.0f);				// 大きさを設定

	playOperate->SetTex("asset/Texture/How_to_play.png");	// 画像読み込み
	playOperate->SetPos(0.0f, -400.0f, 0.0f);				// 座標を設定
	playOperate->SetScale(600.0f, 180.0f, 0.0f);			// 大きさを設定

	frame->SetTex("asset/Texture/Frame.png");				// 画像読み込み
	frame->SetPos(0.0f, -200.0f, 0.0f);						// 座標を設定
	frame->SetScale(800.0f, 200.0f, 0.0f);					// 大きさを設定
	frame->tags.AddTag("frame");							// タグ付け

	fade_In = true;
}

void TitleScene::Update()
{
	if (fade_In == true)
	{
		Fade_In();		// フェードイン処理		(明るくなる)
	}
	
	if (fadeOut_Start == true)
	{
		Fade_Out();	// フェードアウト処理	(暗くなる)
	}

	Frame_Input();	// フレーム移動入力処理
	Frame_Move();	// フレームの移動処理
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
				quad->SetPos(0.0f, -210.0f, 0.0f);				// 座標を設定
				quad->SetScale(800.0f, 200.0f, 0.0f);			// 大きさを設定
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
				quad->SetScale(600.0f, 200.0f, 0.0f);			// 大きさを設定
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
void TitleScene::Fade_Out()
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