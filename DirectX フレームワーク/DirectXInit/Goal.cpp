#include "Goal.h"
#include "Player.h"
#include "GameScene.h"

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
				SceneManager::ChangeScene(RESULT,GameScene::bandTipCount);
			}
		}
	}
}

std::vector<std::string> Goal::GetData() const
{
	std::vector<std::string> buf;
	buf.push_back("Goal");
	auto objectData = Object::GetData();
	buf.insert(buf.end(), objectData.begin(), objectData.end());
	return buf;
}

bool Goal::SetData(std::vector<std::string> _data)
{
	if (_data.front() == "Goal")
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