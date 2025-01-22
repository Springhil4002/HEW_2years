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

std::vector<std::string> Coin::GetData() const
{
	std::vector<std::string> buf;
	buf.push_back("Coin");
	auto objectData = Object::GetData();
	buf.insert(buf.end(), objectData.begin(), objectData.end());
	return buf;
}

bool Coin::SetData(std::vector<std::string> _data)
{
	if (_data.front() == "Coin")
	{
		std::vector<std::string> objBuf(_data.size());
		std::copy(_data.begin() + 1, _data.end(), objBuf.begin());
		Object::SetData(objBuf);

		return true;
	}
	else
	{
		return false;
	}
}