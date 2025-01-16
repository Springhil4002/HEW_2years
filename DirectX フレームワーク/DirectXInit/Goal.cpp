#include "Goal.h"
#include "Player.h"

void Goal::Init()
{
	SetTex("asset/Texture/Door.png");					// �摜�ǂݍ���
	SetScale(BLOCK_SIZE, BLOCK_SIZE * 2, 0.0f);			// �傫����ݒ�
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