#include "ResultScene.h"
#include "SceneManager.h"
#include "Quad.h"

void ResultScene::Init()
{
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM003);	// サウンドを停止
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM005);	// サウンドを再生

	auto bg = Object::Create<Quad>();
	
	bg->SetTex("asset/Texture/Night.jpg");
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
	bg->layer = -1;
}

void ResultScene::Update()
{
	//input.Update();	//キー入力の判定
	// エンターキーを押したら
	if (input.GetKeyTrigger(VK_RETURN))
	{
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
		//現在のシーンを「TitleScene」に切り替える
		SceneManager::ChangeScene(TITLE);
	}
}