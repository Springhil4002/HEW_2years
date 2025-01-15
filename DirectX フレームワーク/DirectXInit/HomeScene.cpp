#include "HomeScene.h"
#include "SceneManager.h"
#include "Quad.h"

HomeScene::HomeScene(int _num)
{
	Init(_num);
}

void HomeScene::Init(int _num)
{
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM001);			// サウンド停止
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);			// サウンド停止
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

		bg->SetTex("asset/Texture/Home.jpg");						// 画像読み込み
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);				// 大きさを設定
		bg->layer = -1;												// レイヤーを設定

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

		bg->SetTex("asset/Texture/Home.jpg");						// 画像読み込み
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);				// 大きさを設定
		bg->layer = -1;												// レイヤーを設定

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
		backTitle->SetScale(100.0f, 80.0f, 0.0f);					// 大きさを設定
		break; }
	default: {
		break; }
	}
}

void HomeScene::Update()
{
	// フレーム移動入力処理
	if (homeSceneNum == 1)
	{
		/* コントローラー:十字下キー
		*  キーボード   :↓矢印キー
		*  どちらかが押されたら
		*/
		if((input.GetButtonTrigger(XINPUT_DOWN) ||
		    input.GetKeyTrigger	  (VK_DOWN)) &&
			frameNum < 3) {		  
			frameNum += 1;		  
		}
		/* コントローラー:十字上キー
		*  キーボード   :↑矢印キー
		*  どちらかが押されたら
		*/
		if((input.GetButtonTrigger(XINPUT_UP) ||
			input.GetKeyTrigger	  (VK_UP)) &&
			frameNum > 0) {
			frameNum -= 1;		  
		}
	}
	if (homeSceneNum == 2)
	{
		/* コントローラー:十字右キー
		*  キーボード   :→矢印キー
		*  どちらかが押されたら
		*/
		if((input.GetButtonTrigger(XINPUT_RIGHT) ||
			input.GetKeyTrigger   (VK_RIGHT)) &&
			frameNum < 8) {
			if (frameNum == 0) {
				frameNum += 4;
			} else {
				frameNum += 1;
			}	
		}
		/* コントローラー:十字左キー
		*  キーボード   :←矢印キー
		*  どちらかが押されたら
		*/
		if((input.GetButtonTrigger(XINPUT_LEFT) ||
			input.GetKeyTrigger	  (VK_LEFT)) &&
			frameNum >= 4) {
			if (frameNum == 4) { 
				frameNum -= 4;
			} else { 
				frameNum -= 1; 
			}
		}
	}
	// ホームシーン切り替えの入力処理
	if (input.GetButtonTrigger	  (XINPUT_RIGHT_SHOULDER) ||
		input.GetKeyTrigger		  (VK_2))
	{
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
		//現在のシーンを「HomeScene(2枚目)」に切り替える
		SceneManager::ChangeScene(HOME_2);
	}
	if (input.GetButtonTrigger	  (XINPUT_LEFT_SHOULDER) ||
		input.GetKeyTrigger		  (VK_1))
	{
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
		//現在のシーンを「HomeScene(1枚目)」に切り替える
		SceneManager::ChangeScene(HOME_1);
	}

	// フレームアイコンの移動処理
	switch (frameNum)
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
		if (input.GetButtonTrigger(XINPUT_B) ||
			input.GetKeyTrigger   (VK_RETURN))
			
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
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
			input.GetButtonTrigger(XINPUT_B))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(GAME_1);
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
			input.GetButtonTrigger(XINPUT_B))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(GAME_2);
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
			input.GetButtonTrigger(XINPUT_B))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(GAME_3);
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
			input.GetButtonTrigger(XINPUT_B))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(GAME_4);
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
			input.GetButtonTrigger(XINPUT_B))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(GAME_5);
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
			input.GetButtonTrigger(XINPUT_B))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(GAME_6);
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
			input.GetButtonTrigger(XINPUT_B))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(GAME_7);
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
			input.GetButtonTrigger(XINPUT_B))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(GAME_8);
		}
		break; }
	default:
		break;
	}
}