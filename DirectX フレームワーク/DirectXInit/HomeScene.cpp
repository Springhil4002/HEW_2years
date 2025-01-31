#include "HomeScene.h"
#include "SceneManager.h"
#include "Quad.h"
#include "Application.h"

// コンストラクタ
HomeScene::HomeScene(int _num)
{
	Init(_num);
}

// 初期化処理
void HomeScene::Init(int _num)
{
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM001);			// サウンド停止
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);			// サウンド停止
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM005);			// サウンド停止
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM002);			// サウンド再生
	homeSceneNum = _num;
		
	// ステージ選択シーンの描画分岐処理
	switch (homeSceneNum) {
	case 1: {
		frameNum = 1;
		// オブジェクトの作成
		auto bg						= Object::Create<Quad>();		// 背景
		auto stage_Logo1			= Object::Create<Quad>();		// ステージロゴ
		auto stage_Logo2			= Object::Create<Quad>();		// ステージロゴ
		auto stage_Logo3			= Object::Create<Quad>();		// ステージロゴ
		auto rightArrow				= Object::Create<Quad>();		// 矢印アイコン
		auto frame					= Object::Create<Quad>();		// アイコンの枠
		auto backTitle				= Object::Create<Quad>();		// タイトルに戻る
		auto howToPlay1				= Object::Create<Quad>();		// 操作説明	決定
		auto howToPlay2				= Object::Create<Quad>();		// 操作説明	LB
		auto howToPlay3				= Object::Create<Quad>();		// 操作説明	RB
		auto howToPlay4				= Object::Create<Quad>();		// 操作説明	上下
		auto howToPlay5				= Object::Create<Quad>();		// 操作説明	左右

		bg->SetTex("asset/Texture/Bg.png");							// 画像読み込み
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);				// 大きさを設定
		bg->layer = -1;												// レイヤーを設定

		// フェードインオブジェクト作成
		auto fade = Object::Create<Quad>();
		fade->SetTex("asset/Texture/Fade.png");		// 画像読み込み
		fade->SetPos(0.0f, 0.0f, 0.0f);				// 座標設定
		fade->SetScale(1920.0f, 1080.0f, 0.0f);		// 大きさを設定
		fade->tags.AddTag("Fade");					// タグ付け
		fade->layer = 10;							// レイヤーを設定

		stage_Logo1->SetTex("asset/Texture/Stage1.png");			// 画像読み込み
		stage_Logo1->SetPos(300.0f, 300.0f, 0.0f);					// 座標を設定
		stage_Logo1->SetScale(400.0f, 150.0f, 0.0f);				// 大きさを設定

		stage_Logo2->SetTex("asset/Texture/Stage2.png");			// 画像読み込み
		stage_Logo2->SetPos(400.0f, 0.0f, 0.0f);					// 座標を設定
		stage_Logo2->SetScale(400.0f, 150.0f, 0.0f);				// 大きさを設定

		stage_Logo3->SetTex("asset/Texture/Stage3.png");			// 画像読み込み
		stage_Logo3->SetPos(300.0f, -300.0f, 0.0f);					// 座標を設定
		stage_Logo3->SetScale(400.0f, 150.0f, 0.0f);				// 大きさを設定

		rightArrow->SetTex("asset/Texture/ToHome_2.png");			// 画像読み込み
		rightArrow->SetPos(800.0f, 0.0f, 0.0f);						// 座標を設定
		rightArrow->SetScale(200.0f, 75.0f, 0.0f);					// 大きさを設定
			
		frame->SetTex("asset/Texture/Frame.png");					// 画像読み込み
		frame->SetPos(300.0f, 300.0f, 0.0f);						// 座標を設定
		frame->SetScale(420.0f, 150.0f, 0.0f);						// 大きさを設定
		frame->tags.AddTag("frame");								// タグ付け

		backTitle->SetTex("asset/Texture/BackTitle.png");			// 画像読み込み
		backTitle->SetPos(-900.0f, 480.0f, 0.0f);					// 座標を設定
		backTitle->SetScale(100.0f, 100.0f, 0.0f);					// 大きさを設定

		howToPlay1->SetTex("asset/Texture/Decision_Logo.png");		// 画像読み込み
		howToPlay1->SetPos(-400.0f, 300.0f, 0.0f);					// 座標設定
		howToPlay1->SetScale(400.0f, 150.0f, 0.0f);					// 大きさを設定

		howToPlay2->SetTex("asset/Texture/LB_Logo.png");			// 画像読み込み
		howToPlay2->SetPos(-400.0f, 150.0f,0.0f);					// 座標設定
		howToPlay2->SetScale(800.0f, 150.0f, 0.0f);					// 大きさを設定
		
		howToPlay3->SetTex("asset/Texture/RB_Logo.png");			// 画像読み込み
		howToPlay3->SetPos(-400.0f, 0.0f, 0.0f);					// 座標設定
		howToPlay3->SetScale(800.0f, 150.0f, 0.0f);					// 大きさを設定

		howToPlay4->SetTex("asset/Texture/LeftRight_Logo.png");		// 画像読み込み
		howToPlay4->SetPos(-400.0f, -150.0f, 0.0f);					// 座標設定
		howToPlay4->SetScale(600.0f, 150.0f, 0.0f);					// 大きさを設定

		howToPlay5->SetTex("asset/Texture/UpDown_Logo.png");		// 画像読み込み
		howToPlay5->SetPos(-400.0f, -300.0f, 0.0f);					// 座標設定
		howToPlay5->SetScale(600.0f, 150.0f, 0.0f);					// 大きさを設定

		break; }
	case 2: {
		frameNum = 4;		
		auto bg						= Object::Create<Quad>();		// 背景
		auto stage_Logo4			= Object::Create<Quad>();		// ステージロゴ
		auto stage_Logo5			= Object::Create<Quad>();		// ステージロゴ
		auto stage_Logo6			= Object::Create<Quad>();		// ステージロゴ
		auto stage_Logo7			= Object::Create<Quad>();		// ステージロゴ
		auto stage_Logo8			= Object::Create<Quad>();		// ステージロゴ
		auto leftArrow				= Object::Create<Quad>();		// 矢印アイコン
		auto frame					= Object::Create<Quad>();		// アイコンを囲むフレーム
		auto backTitle				= Object::Create<Quad>();		// タイトルに戻る

		bg->SetTex("asset/Texture/Bg.png");							// 画像読み込み
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);				// 大きさを設定
		bg->layer = -1;												// レイヤーを設定

		// フェードイン・フェードアウト用
		auto fade = Object::Create<Quad>();
		fade->SetTex("asset/Texture/Fade_Black.png",			// 画像読み込み
			1, 1, 0, 0, 1.0f, 1.0f, 1.0f, 1.0f);
		fade->SetPos(0.0f, 0.0f, 0.0f);							// 座標設定
		fade->SetScale(1920.0f, 1080.0f, 0.0f);					// 大きさを設定
		fade->tags.AddTag("Fade");								// タグ付け
		fade->layer = 2;										// レイヤーを設定


		stage_Logo4->SetTex("asset/Texture/Stage4.png");			// 画像読み込み
		stage_Logo4->SetPos(-450.0f, 300.0f, 0.0f);					// 座標を設定
		stage_Logo4->SetScale(400.0f, 150.0f, 0.0f);				// 大きさを設定

		stage_Logo5->SetTex("asset/Texture/Stage5.png");			// 画像読み込み
		stage_Logo5->SetPos(0.0f, 300.0f, 0.0f);					// 座標を設定
		stage_Logo5->SetScale(400.0f, 150.0f, 0.0f);				// 大きさを設定

		stage_Logo6->SetTex("asset/Texture/Stage6.png");			// 画像読み込み
		stage_Logo6->SetPos(450.0f, 300.0f, 0.0f);					// 座標を設定
		stage_Logo6->SetScale(400.0f, 150.0f, 0.0f);				// 大きさを設定

		stage_Logo7->SetTex("asset/Texture/Stage7.png");			// 画像読み込み
		stage_Logo7->SetPos(-300.0f, -300.0f, 0.0f);				// 座標を設定
		stage_Logo7->SetScale(400.0f, 150.0f, 0.0f);				// 大きさを設定

		stage_Logo8->SetTex("asset/Texture/Stage8.png");			// 画像読み込み
		stage_Logo8->SetPos(300.0f, -300.0f, 0.0f);					// 座標を設定
		stage_Logo8->SetScale(400.0f, 150.0f, 0.0f);				// 大きさを設定

		leftArrow->SetTex("asset/Texture/ToHome_1.png");			// 画像読み込み
		leftArrow->SetPos(-800.0f, 0.0f, 0.0f);						// 座標を設定
		leftArrow->SetScale(200.0f, 75.0f, 0.0f);					// 大きさを設定

		frame->SetTex("asset/Texture/Frame.png");					// 画像読み込み
		frame->SetPos(-450.0f, 300.0f, 0.0f);						// 座標を設定
		frame->SetScale(420.0f, 150.0f, 0.0f);						// 大きさを設定
		frame->tags.AddTag("frame");								// タグ付け

		backTitle->SetTex("asset/Texture/BackTitle.png");			// 画像読み込み
		backTitle->SetPos(-900.0f, 480.0f, 0.0f);					// 座標を設定
		backTitle->SetScale(100.0f, 100.0f, 0.0f);					// 大きさを設定
		break; }
	default: {
		break; }
	}
}

// 更新処理
void HomeScene::Update()
{
	if (fade_In = true)
	{
		// フェードイン処理	(明るくなる)
		Fade_In();
	}
	Frame_Input();	// frame移動入力処理
	Frame_Move();	// frame移動処理
	ChangeHome();	// HomeScene切り替え処理

	// フェードアウト処理	(暗くなる)
	if (fadeOut_Start == true)
	{
		Fade_Out();	
	}

	auto objects = objectInstance;
	for (auto& obj : objects)
	{
		obj->Update();
	}
}

// フレーム移動入力処理
void HomeScene::Frame_Input()
{
	if (GetHomeSceneNum() == 1)
	{
		/* コントローラー:十字下キー
		*  キーボード   :↓矢印キー
		*  どちらかが押されたら
		*/
		if ((input.GetButtonTrigger(XINPUT_DOWN) ||
			input.GetKeyTrigger(VK_DOWN)) &&
			GetFrameNum() < 3) {
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE003);	// 選択音
			SetFrameNum(GetFrameNum() + 1);
		}
		/* コントローラー:十字上キー
		*  キーボード   :↑矢印キー
		*  どちらかが押されたら
		*/
		if ((input.GetButtonTrigger(XINPUT_UP) ||
			input.GetKeyTrigger(VK_UP)) &&
			GetFrameNum() > 0) {
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE003);	// 選択音
			SetFrameNum(GetFrameNum() - 1);
		}
	}
	if (GetHomeSceneNum() == 2)
	{
		/* コントローラー:十字右キー
		*  キーボード   :→矢印キー
		*  どちらかが押されたら
		*/
		if ((input.GetButtonTrigger(XINPUT_RIGHT) ||
			input.GetKeyTrigger(VK_RIGHT)) &&
			GetFrameNum() < 8) {
			if (GetFrameNum() == 0) {
				SceneManager::m_SoundManager.Play(SOUND_LABEL_SE003);	// 選択音
				SetFrameNum(GetFrameNum() + 4);
			}
			else {
				SceneManager::m_SoundManager.Play(SOUND_LABEL_SE003);	// 選択音
				SetFrameNum(GetFrameNum() + 1);
			}
		}
		/* コントローラー:十字左キー
		*  キーボード   :←矢印キー
		*  どちらかが押されたら
		*/
		if ((input.GetButtonTrigger(XINPUT_LEFT) ||
			input.GetKeyTrigger(VK_LEFT)) &&
			GetFrameNum() >= 4) {
			if (GetFrameNum() == 4) {
				SceneManager::m_SoundManager.Play(SOUND_LABEL_SE003);	// 選択音
				SetFrameNum(GetFrameNum() - 4);
			}
			else {
				SceneManager::m_SoundManager.Play(SOUND_LABEL_SE003);	// 選択音
				SetFrameNum(GetFrameNum() - 1);
			}
		}
	}
}

// フレーム移動処理
void HomeScene::Frame_Move()
{
	// フレームアイコンの移動処理
	switch (GetFrameNum())
	{
	case 0: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(-900.0f, 480.0f, 0.0f);		// 座標を設定
				quad->SetScale(100.0f, 130.0f, 0.0f);		// 大きさを設定
			}
		}
		// エンターキーorBボタンを押したら
		if (input.GetButtonTrigger(XINPUT_A) ||
			input.GetKeyTrigger(VK_RETURN))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// 決定音
		}
		if (fadeOut_End == true)
		{
			//現在のシーンを「TitleScene」に切り替える
			SceneManager::ChangeScene(TITLE);
		}
		break; }
	case 1: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(300.0f, 300.0f, 0.0f);			// 座標を設定
				quad->SetScale(420.0f, 150.0f, 0.0f);		// 大きさを設定
			}
		}
		// エンターキーorBボタンを押したら
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// 決定音
		}
		if (fadeOut_End == true)
		{
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(GAME_1, 1);
		}
		break; }
	case 2: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(400.0f, 0.0f, 0.0f);			// 座標を設定
				quad->SetScale(420.0f, 150.0f, 0.0f);		// 大きさを設定
			}
		}
		// エンターキーorBボタンを押したら
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// 決定音
		}
		if (fadeOut_End == true)
		{
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(GAME_2, 2);
		}
		break; }
	case 3: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(300.0f, -300.0f, 0.0f);		// 座標を設定
				quad->SetScale(420.0f, 150.0f, 0.0f);		// 大きさを設定
			}
		}
		// エンターキーorBボタンを押したら
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// 決定音
		}
		if (fadeOut_End == true)
		{
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(GAME_3, 3);
		}
		break; }
	case 4: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(-450.0f, 300.0f, 0.0f);		// 座標を設定
				quad->SetScale(420.0f, 150.0f, 0.0f);		// 大きさを設定
			}
		}
		// エンターキーorBボタンを押したら
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// 決定音
		}
		if (fadeOut_End == true)
		{
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(GAME_4, 4);
		}
		break; }
	case 5: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(0.0f, 300.0f, 0.0f);			// 座標を設定
				quad->SetScale(420.0f, 150.0f, 0.0f);		// 大きさを設定
			}
		}
		// エンターキーorBボタンを押したら
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// 決定音
		}
		if (fadeOut_End == true)
		{
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(GAME_5, 5);
		}
		break; }
	case 6: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(450.0f, 300.0f, 0.0f);			// 座標を設定
				quad->SetScale(420.0f, 150.0f, 0.0f);		// 大きさを設定
			}
		}
		// エンターキーorBボタンを押したら
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// 決定音
			
		}
		if (fadeOut_End == true)
		{
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(GAME_6, 6);
		}
		break; }
	case 7: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(-300.0f, -300.0f, 0.0f);		// 座標を設定
				quad->SetScale(420.0f, 150.0f, 0.0f);		// 大きさを設定
			}
		}
		// エンターキーorBボタンを押したら
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// 決定音
		}
		if (fadeOut_End == true)
		{
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(GAME_7, 7);
		}
		break; }
	case 8: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(300.0f, -300.0f, 0.0f);		// 座標を設定
				quad->SetScale(420.0f, 150.0f, 0.0f);		// 大きさを設定
			}
		}
		// エンターキーorBボタンを押したら
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// 決定音
		}
		if (fadeOut_End == true)
		{
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(GAME_8, 8);
		}
		break; }
	default:
		break;
	}
}

// HomwScene切り替え処理
void HomeScene::ChangeHome()
{
	/*コントローラー:RBボタン
	 *キーボード   :2キー
	 * どちらかが押されたら
	 */
	if (input.GetButtonTrigger(XINPUT_RIGHT_SHOULDER) ||
		input.GetKeyTrigger	  (VK_2))
	{
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// 決定音
		//現在のシーンを「HomeScene(2枚目)」に切り替える
		SceneManager::ChangeScene(HOME_2,2);
	}

	/*コントローラー:LBボタン
	 *キーボード   :1キー
	 * どちらかが押されたら
	 */
	if (input.GetButtonTrigger(XINPUT_LEFT_SHOULDER) ||
		input.GetKeyTrigger	  (VK_1))
	{
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// 決定音
		//現在のシーンを「HomeScene(1枚目)」に切り替える
		SceneManager::ChangeScene(HOME_1,1);
	}
}

// フェードイン処理		(明るくなる)
void HomeScene::Fade_In()
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
					fade->SetTex("asset/Texture/Fade_In_1.png");	// 画像読み込み
					break; }
				case 2: {
					fade->SetTex("asset/Texture/Fade_In_2.png");	// 画像読み込み
					break; }
				case 3: {
					fade->SetTex("asset/Texture/Fade_In_3.png");	// 画像読み込み
					break; }
				case 4: {
					fade->SetTex("asset/Texture/Fade_In_4.png");	// 画像読み込み
					break; }
				case 5: {
					fade->SetTex("asset/Texture/Fade_In_5.png");	// 画像読み込み
					break; }
				case 6: {
					fade->SetTex("asset/Texture/Fade_In_6.png");	// 画像読み込み
					break; }
				case 7: {
					fade->SetTex("asset/Texture/Fade_In_7.png");	// 画像読み込み
					break; }
				case 8: {
					fade->SetTex("asset/Texture/Fade_In_8.png");	// 画像読み込み
					break; }
				case 9: {
					fade->SetTex("asset/Texture/Fade_In_9.png");	// 画像読み込み
					break; }
				case 10: {
					fade->SetTex("asset/Texture/Fade_In_10.png");	// 画像読み込み
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

// フェードアウト処理	(暗くなる)
void HomeScene::Fade_Out()
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
				fade->SetTex("asset/Texture/Fade_Out_1.png");	// 画像読み込み
				break; }
			case 2: {
				fade->SetTex("asset/Texture/Fade_Out_2.png");	// 画像読み込み
				break; }
			case 3: {
				fade->SetTex("asset/Texture/Fade_Out_3.png");	// 画像読み込み
				break; }
			case 4: {
				fade->SetTex("asset/Texture/Fade_Out_4.png");	// 画像読み込み
				break; }
			case 5: {
				fade->SetTex("asset/Texture/Fade_Out_5.png");	// 画像読み込み
				break; }
			case 6: {
				fade->SetTex("asset/Texture/Fade_Out_6.png");	// 画像読み込み
				break; }
			case 7: {
				fade->SetTex("asset/Texture/Fade_Out_7.png");	// 画像読み込み
				break; }
			case 8: {
				fade->SetTex("asset/Texture/Fade_Out_8.png");	// 画像読み込み
				break; }
			case 9: {
				fade->SetTex("asset/Texture/Fade_Out_9.png");	// 画像読み込み
				break; }
			case 10: {
				fade->SetTex("asset/Texture/Fade_Out_10.png");	// 画像読み込み
				break; }
			default: {
				fade->SetColor(1.0f, 1.0f, 1.0f, 0.0f);
				fade->SetTex("asset/Texture/Fade.png");		// 画像読み込み
				fadeOut_End = true;
				break; }
			}
		}
	}
}