#include "Coin.h"
#include "Player.h"

void Coin::Init()
{
	SetTex("asset/Texture/player.png");// ƒvƒŒƒCƒ„[‚ð‰Šú‰»
	SetScale(BLOCK_SIZE * 3, BLOCK_SIZE * 3, 0.0f);	// ‘å‚«‚³‚ðÝ’è
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
			// ‚Õ‚ê‚¢‚³‚¤‚ñ‚Ç
			//
			
			Object::Delete(this);
		}
	}
}