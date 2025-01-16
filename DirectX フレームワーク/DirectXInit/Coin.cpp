#include "Coin.h"
#include "Player.h"
#include "GameScene.h"

void Coin::Init()
{
	SetTex("asset/Texture/Coin.png");// プレイヤーを初期化
	SetScale(BLOCK_SIZE, BLOCK_SIZE, 0.0f);	// 大きさを設定
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