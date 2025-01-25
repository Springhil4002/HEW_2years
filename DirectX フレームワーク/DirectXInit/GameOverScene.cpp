#include "GameOverScene.h"
#include "SceneManager.h"
#include "Quad.h"

SCENE GameOverScene::isEndSceneNum = GAME_1;

// 初期化処理
void GameOverScene::Init()
{
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM003);		// サウンドを停止
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM004);		// サウンドを再生

	// オブジェクトの作成
	auto bg							= Object::Create<Quad>();	// 背景
	auto logo						= Object::Create<Quad>();	// ゲームオーバーロゴ
	auto returnTitle				= Object::Create<Quad>();	//「タイトルに戻る」アイコン
	auto returnHome					= Object::Create<Quad>();	//「ステージ選択に戻る」アイコン
	auto retryLogo					= Object::Create<Quad>();	//「リトライ」アイコン
	auto frame						= Object::Create<Quad>();	// アイコンを囲むフレーム

	bg->SetTex("asset/Texture/GameOver_bg.png");				// 画像読み込み
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);				// 大きさを設定
	bg->layer = -1;												// レイヤーを設定

	logo->SetTex("asset/Texture/GameOver.png");					// 画像読み込み
	logo->SetPos(0.0f, 300.0f, 0.0f);							// 座標を設定
	logo->SetScale(600.0f, 400.0f, 0.0f);						// 大きさを設定

	returnTitle->SetTex("asset/Texture/Return_toTitle.png");	// 画像読み込み
	returnTitle->SetPos(-450.0f, -300.0f, 0.0f);				// 座標を設定
	returnTitle->SetScale(420.0f, 150.0f, 0.0f);				// 大きさを設定

	returnHome->SetTex("asset/Texture/Return_toHome.png");		// 画像読み込み
	returnHome->SetPos(0.0f, -300.0f, 0.0f);					// 座標を設定
	returnHome->SetScale(420.0f, 150.0f, 0.0f);					// 大きさを設定

	retryLogo->SetTex("asset/Texture/Retry.png");				// 画像読み込み
	retryLogo->SetPos(450.0f, -300.0f, 0.0f);					// 座標を設定
	retryLogo->SetScale(420.0f, 150.0f, 0.0f);					// 大きさを設定

	frame->SetTex("asset/Texture/Frame.png");					// 画像読み込み
	frame->SetPos(-450.0f, -300.0f, 0.0f);						// 座標を設定
	frame->SetScale(420.0f, 150.0f, 0.0f);						// 大きさを設定
	frame->tags.AddTag("frame");								// タグ付け
}
// 更新処理
void GameOverScene::Update()
{
	Frame_Input();		// フレーム移動入力処理
	Frame_Move();		// フレーム移動処理
}

// フレーム移動入力処理
void GameOverScene::Frame_Input()
{
	/*コントローラー:十字右キー
	 *キーボード　　:→矢印キー
	 *どちらかが押されたら
	 */
	if ((input.GetButtonTrigger(XINPUT_RIGHT) ||
		input.GetKeyTrigger(VK_RIGHT)) &&
		GetFrameNum() < 3) {
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE003);	// 選択音
		SetFrameNum(GetFrameNum() + 1);
	}
	/*コントローラー:十字左キー
	 *キーボード　　:←矢印キー
	 *どちらかが押されたら
	 */
	if ((input.GetButtonTrigger(XINPUT_LEFT) ||
		input.GetKeyTrigger(VK_LEFT)) &&
		GetFrameNum() > 1) {
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE003);	// 選択音
		SetFrameNum(GetFrameNum() - 1);
	}
}

// フレーム移動処理
void GameOverScene::Frame_Move()
{
	// フレーム移動処理・入力後の各シーン遷移処理
	switch (GetFrameNum())
	{
	case 1: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(-450.0f, -300.0f, 0.0f);
			}
		}
		// エンターキーorBボタンを押したら
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// 決定音
			//現在のシーンを「TitleScene」に切り替える
			SceneManager::ChangeScene(TITLE);
		}
		break; }
	case 2: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(0.0f, -300.0f, 0.0f);
			}
		}
		// エンターキーorBボタンを押したら
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// 決定音
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(HOME_1,1);
		}
		break; }
	case 3: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(450.0f, -300.0f, 0.0f);
			}
		}
		// エンターキーorBボタンを押したら
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// 決定音
			int stageNum = (int)(GameOverScene::isEndSceneNum - SCENE_ENUM_OFFSET);
			//現在のシーンを直前にゲームオーバーした「GameScene」に切り替える
			SceneManager::ChangeScene(isEndSceneNum,stageNum);
		}
		break; }
	default:
		break;
	}
}