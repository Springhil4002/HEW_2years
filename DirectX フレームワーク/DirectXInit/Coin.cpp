#include "Coin.h"
#include "Player.h"

void Coin::Init()
{
	SetTex("asset/Texture/player.png");// プレイヤーを初期化
	SetScale(BLOCK_SIZE * 3, BLOCK_SIZE * 3, 0.0f);	// 大きさを設定
}

void Coin::Update()
{
	Quad::Update();
	auto player = Scene::GetInstance()->GetObjects<Player>();
	for (auto& pl : player)
	{
		if (Object::Collision(this, pl))
		{
			//
			// ぷれいさうんど
			//
			
			Object::Delete(this);
		}
	}
}