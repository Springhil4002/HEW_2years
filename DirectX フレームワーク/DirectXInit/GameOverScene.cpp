#include "GameOverScene.h"
#include "SceneManager.h"
#include "Quad.h"

// コンストラクタ(初期化処理)
GameOverScene::GameOverScene()
{

}

// デストラクタ	(解放処理)
GameOverScene::~GameOverScene()
{

}

// 初期化処理
void GameOverScene::Init()
{
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// サウンドを停止
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM005);	// サウンドを再生
	auto bg = Object::Create<Quad>();
	auto logo = Object::Create<Quad>();
	auto returnTitle = Object::Create<Quad>();
	auto returnHome = Object::Create<Quad>();
	auto frame = Object::Create<Quad>();

	bg->SetTex("asset/Texture/GameOver_bg.png");
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
	bg->layer = -1;

	logo->SetTex("asset/Texture/GameOver.png");
	logo->SetPos(0.0f, 300.0f, 0.0f);
	logo->SetScale(600.0f, 400.0f, 0.0f);

	returnTitle->SetTex("asset/Texture/Return_toTitle.png");
	returnTitle->SetPos(-300.0f, -300.0f, 0.0f);
	returnTitle->SetScale(420.0f, 150.0f, 0.0f);

	returnHome->SetTex("asset/Texture/Return_toHome.png");
	returnHome->SetPos(300.0f, -300.0f, 0.0f);
	returnHome->SetScale(420.0f, 150.0f, 0.0f);

	frame->SetTex("asset/Texture/Frame.png");
	frame->SetPos(-300.0f, 300.0f, 0.0f);
	frame->SetScale(420.0f, 150.0f, 0.0f);
	frame->tags.AddTag("frame");
}
// 更新処理
void GameOverScene::Update()
{
	if (input.GetKeyTrigger(VK_D) ||
		input.GetKeyTrigger(VK_A) ||
		input.GetButtonTrigger(XINPUT_RIGHT) ||
		input.GetButtonTrigger(XINPUT_LEFT))
	{
		if((input.GetButtonTrigger(XINPUT_RIGHT) ||
			input.GetKeyTrigger(VK_D)) &&
			frameNum < 2) {
			frameNum += 1;
		}
		if ((input.GetButtonTrigger(XINPUT_LEFT) ||
			input.GetKeyTrigger(VK_A)) &&
			frameNum > 1) {
			frameNum -= 1;
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
				quad->SetPos(-300.0f, -300.0f, 0.0f);
			}
		}

		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_B))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE001);
			//現在のシーンを「TitleScene」に切り替える
			SceneManager::ChangeScene(SceneManager::TITLE);
		}
		break; }
	case 2: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(300.0f, -300.0f, 0.0f);
			}
		}

		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_B))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE001);
			//現在のシーンを「GameScene」に切り替える
			SceneManager::ChangeScene(SceneManager::HOME_1);
		}
		break; }
	default:
		break;
	}
}