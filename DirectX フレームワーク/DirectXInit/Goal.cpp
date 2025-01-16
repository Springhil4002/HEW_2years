#include "Goal.h"
#include "Player.h"

void Goal::Init()
{
	SetTex("asset/Texture/Door.png");					// ‰æ‘œ“Ç‚Ýž‚Ý
	SetScale(BLOCK_SIZE, BLOCK_SIZE * 2, 0.0f);			// ‘å‚«‚³‚ðÝ’è
}

void Goal::Update()
{
	Quad::Update();
	auto player = Scene::GetInstance()->GetObjects<Player>();
	for (auto& pl : player)
	{
		if (Object::Collision(this, pl))
		{
			if((Scene::input.GetRightTrigger() >= 0.9 &&
				Scene::input.GetLeftTrigger() >= 0.9) ||
				Scene::input.GetKeyTrigger(VK_E))
			{
				SceneManager::ChangeScene(RESULT);
			}
		}
	}
}