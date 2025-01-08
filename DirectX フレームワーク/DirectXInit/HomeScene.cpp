#include "HomeScene.h"
#include "SceneManager.h"
#include "Quad.h"

HomeScene::HomeScene()
{
	
}

HomeScene::~HomeScene()
{

}

void HomeScene::Init()
{
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM001);	// サウンド停止
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM004);	// サウンド再生
	switch (homeSceneNum) {
	case 1: {
		auto bg = Object::Create<Quad>();
		auto stage_Logo1 = Object::Create<Quad>();
		auto stage_Logo2 = Object::Create<Quad>();
		auto stage_Logo3 = Object::Create<Quad>();
		auto frame = Object::Create<Quad>();

		bg->SetTex("asset/Texture/Home.jpg");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);

		stage_Logo1->SetTex("asset/Texture/Stage1.png");
		stage_Logo1->SetPos(300.0f, 300.0f, 0.0f);
		stage_Logo1->SetScale(400.0f, 150.0f, 0.0f);

		stage_Logo2->SetTex("asset/Texture/Stage2.png");
		stage_Logo2->SetPos(400.0f, 0.0f, 0.0f);
		stage_Logo2->SetScale(400.0f, 150.0f, 0.0f);

		stage_Logo3->SetTex("asset/Texture/Stage3.png");
		stage_Logo3->SetPos(300.0f, -300.0f, 0.0f);
		stage_Logo3->SetScale(400.0f, 150.0f, 0.0f);

		frame->SetTex("asset/Texture/Frame.png");
		frame->SetPos(300.0f, 300.0f, 0.0f);
		frame->SetScale(420.0f, 150.0f, 0.0f);
		frame->tags.AddTag("frame");
		break; }
	case 2: {
		auto bg = Object::Create<Quad>();
		auto stage_Logo4 = Object::Create<Quad>();
		auto stage_Logo5 = Object::Create<Quad>();
		auto stage_Logo6 = Object::Create<Quad>();
		auto stage_Logo7 = Object::Create<Quad>();
		auto stage_Logo8 = Object::Create<Quad>();

		bg->SetTex("asset/Texture/Home.jpg");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);

		stage_Logo4->SetTex("asset/Texture/Stage4.png");
		stage_Logo4->SetPos(-300.0f, 300.0f, 0.0f);
		stage_Logo4->SetScale(400.0f, 150.0f, 0.0f);

		stage_Logo5->SetTex("asset/Texture/Stage5.png");
		stage_Logo5->SetPos(0.0f, 300.0f, 0.0f);
		stage_Logo5->SetScale(400.0f, 150.0f, 0.0f);

		stage_Logo6->SetTex("asset/Texture/Stage6.png");
		stage_Logo6->SetPos(300.0f, 300.0f, 0.0f);
		stage_Logo6->SetScale(400.0f, 150.0f, 0.0f);

		stage_Logo7->SetTex("asset/Texture/Stage7.png");
		stage_Logo7->SetPos(-450.0f, -300.0f, 0.0f);
		stage_Logo7->SetScale(400.0f, 150.0f, 0.0f);

		stage_Logo8->SetTex("asset/Texture/Stage8.png");
		stage_Logo8->SetPos(450.0f, -300.0f, 0.0f);
		stage_Logo8->SetScale(400.0f, 150.0f, 0.0f);
		break; }
	default: {
		break; }
	}
}

void HomeScene::Update()
{
	if(input.GetKeyTrigger(VK_W)||
	   input.GetKeyTrigger(VK_S)||
	   input.GetButtonTrigger(XINPUT_UP)||
	   input.GetButtonTrigger(XINPUT_DOWN))
	{
		if ((input.GetButtonTrigger(XINPUT_UP) || 
			 input.GetKeyTrigger(VK_W)) &&
			frameNum > 1) {
			frameNum -= 1;
		}
		if ((input.GetButtonTrigger(XINPUT_DOWN) ||
			input.GetKeyTrigger(VK_S)) &&
			frameNum < 3) {
			frameNum += 1;
		}
	}

	switch (frameNum)
	{
	case 1: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(300.0f, 300.0f, 0.0f);
			}
		}
		// エンターキーorBボタンを押したら
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_B))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(SceneManager::GAME);
		}
		break; }
	case 2: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(400.0f, 0.0f, 0.0f);
			}
		}
		// エンターキーorBボタンを押したら
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_B))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(SceneManager::GAME);
		}
		break; }
	case 3: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(300.0f, -300.0f, 0.0f);
			}
		}
		// エンターキーorBボタンを押したら
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_B))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(SceneManager::GAME);
		}
		break; }
	default:
		break;
	}
}