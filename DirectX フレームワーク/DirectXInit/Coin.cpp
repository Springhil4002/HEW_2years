#include "Coin.h"
#include "Player.h"

void Coin::Init()
{
	SetTex("asset/Texture/player.png");// �v���C���[��������
	SetScale(BLOCK_SIZE * 3, BLOCK_SIZE * 3, 0.0f);	// �傫����ݒ�
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
			
			Object::Delete(this);
		}
	}
}