#include "Coin.h"
#include "Player.h"
#include "GameScene.h"

void Coin::Init()
{
	SetTex("asset/Texture/Coin.png");// ƒvƒŒƒCƒ„[‚ð‰Šú‰»
	SetScale(BLOCK_SIZE, BLOCK_SIZE, 0.0f);	// ‘å‚«‚³‚ðÝ’è
}

void Coin::Update()
{
	Quad::Update();
	auto player = Scene::GetInstance()->GetObjects<Player>();
	for (auto& pl : player)
	{
		if (Object::Collision(this, pl))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE003);
			
			GameScene::bandTipCount += 1;
			
			Object::Delete(this);
		}
	}
}