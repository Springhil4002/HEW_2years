#include "TitleScene.h"
#include "SceneManager.h"
#include "Quad.h"

TitleScene::TitleScene()
{
	
}

TitleScene::~TitleScene()
{
	
}

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
				
	bg->SetTex("asset/Texture/Title_bg.jpg");				// 画像読み込み
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);			// 大きさを設定
	bg->layer = -1;											// レイヤー設定

	titleLogo->SetTex("asset/Texture/Title_Logo.png");		// 画像読み込み
	titleLogo->SetPos(0.0f, 200.0f, 0.0f);					// 座標を設定
	titleLogo->SetScale(800.0f, 350.0f, 0.0f);				// 大きさを設定

	gameStart->SetTex("asset/Texture/Start_Logo.png");		// 画像読み込み
	gameStart->SetPos(0.0f, -200.0f, 0.0f);					// 座標を設定
	gameStart->SetScale(600.0f, 200.0f, 0.0f);				// 大きさを設定

	playOperate->SetTex("asset/Texture/How_to_play.png");	// 画像読み込み
	playOperate->SetPos(0.0f, -400.0f, 0.0f);				// 座標を設定
	playOperate ->SetScale(400.0f, 150.0f, 0.0f);			// 大きさを設定

	frame->SetTex("asset/Texture/Frame.png");				// 画像読み込み
	frame->SetPos(0.0f, -200.0f, 0.0f);						// 座標を設定
	frame->SetScale(600.0f, 200.0f, 0.0f);					// 大きさを設定
	frame->tags.AddTag("frame");							// タグ付け
}

void TitleScene::Update()
{
	// コントローラー・キーボードの入力処理
	if ((input.GetButtonTrigger(XINPUT_DOWN) ||
		input.GetButtonTrigger(XINPUT_RIGHT) ||
		input.GetKeyTrigger(VK_S) ||
		input.GetKeyTrigger(VK_D)) &&
		frameNum < 2) {
		frameNum += 1;
	}
	if ((input.GetButtonTrigger(XINPUT_UP) ||
		input.GetButtonTrigger(XINPUT_LEFT) ||
		input.GetKeyTrigger(VK_W) ||
		input.GetKeyTrigger(VK_A)) &&
		frameNum > 1) {
		frameNum -= 1;
	}

	// フレームの移動処理
	switch (frameNum)
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
			input.GetButtonTrigger(XINPUT_B))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
			//現在のシーンを「HomeScene」に切り替える
			SceneManager::ChangeScene(HOME_1);
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
			input.GetButtonTrigger(XINPUT_B))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
			//現在のシーンを「PlayOperateScene」に切り替える
			SceneManager::ChangeScene(PLAYOPERATE);
		}
		break; }
	default:
		break;
	}
}

//void TitleScene::Draw()
//{
//	bg.Draw();		// 背景を描画
//}