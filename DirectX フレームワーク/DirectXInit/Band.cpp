#include "Band.h"
#include "GameScene.h"
#include "Ground.h"
#include "UpBand.h"
#include "Player.h"

Band::Band() : L(4)
{
	tip = Object::Create<BandTip>(); 
	tip->band = this;
}

void Band::Init()
{
	delay = Object::Create<Delay>();
	sendDelay = false;

	status = DEFAULT;

	SetTex("asset/Texture/Band_Block.png");
	SetScale(60, 60, 0);
	
	// 先端の初期設定
	tip->SetPos(m_Position.x - BLOCK_SIZE * 2.0f, m_Position.y, 0);
	oldPos = { m_Position.x - BLOCK_SIZE * 2.0f, m_Position.y, 0 };

	for (int i = 0; i < L + 1; i++)
	{
		Quad* buf;
		if (i == 0)
		{
			buf = Object::Create<Entity>();
			buf->SetTex("asset/Texture/Band_Tip.png");
			buf->SetScale(BLOCK_SIZE, BLOCK_SIZE, 0);
		}
		else
		{
			buf = Object::Create<Quad>();
			buf->SetTex("asset/Texture/Band_meter.png");
			buf->SetScale(BLOCK_SIZE, BLOCK_SIZE / 2, 0);
		}
		buf->SetPos(m_Position.x + 60 * (i - 1), m_Position.y, 0);
		buf->layer = layer - 1;
		jagged.insert(buf);
	}

	ResetObject();
}

void Band::Update()
{
	
	// 先端の差の計算
	DirectX::SimpleMath::Vector3 differencial = tip->GetPos() - oldPos;
	// 位置の調整
	for (auto& obj : jagged)
	{
		auto temp = obj->GetPos() + differencial;
		obj->SetPos(temp.x, temp.y, temp.z);
	}

	if (status == DEFAULT || status == REVERSE)
	{
		for (auto& obj : objects)
		{
			auto temp = obj->GetPos() + differencial;
			obj->SetPos(temp.x, temp.y, temp.z);
		}
	}
	
	oldPos = tip->GetPos();
	pullLevel += differencial.x;
	tip->SetPullLeveL(pullLevel);

	bool flg = false;
	switch (status)
	{
	case Band::DEFAULT:
		if (GameScene::player)
		{
			if (GameScene::player->grabState == Player::DEFAULT)
			{
				tip->m_Position.x = (int)(tip->m_Position.x - 1230) / 60 * 60 + 1230;
				for (auto& obj : objects)
				{
					auto temp = obj->GetPos();
					obj->SetPos((int)(temp.x - 1260) / 60 * 60 + 1230, temp.y, temp.z);
				}
				tip->SetVelo(0, 0, 0);
			}
		}
		if (tip->isGrabing)
		{
			for (auto& obj : objects)
			{
				if (dynamic_cast<Ground*>(obj) != nullptr || dynamic_cast<Band*>(obj) != nullptr || dynamic_cast<UpBand*>(obj) != nullptr)
				{
					for (auto& col : Scene::GetInstance()->GetObjects<Ground>())
					{
						if (Object::Collision(obj, col))
						{
							flg = true;
							break;
						}
					}
					for (auto& col : Scene::GetInstance()->GetObjects<Band>())
					{
						if (Object::Collision(obj, col))
						{
							flg = true;
							break;
						}
					}
					for (auto& col : Scene::GetInstance()->GetObjects<UpBand>())
					{
						if (Object::Collision(obj, col))
						{
							flg = true;
							break;
						}
					}
					if (flg)
						break;
				}
			}
		}

		if (flg)
		{
			status = STOP;
			tip->SetVelo(0, 0, 0);
			dynamic_cast<Player*>(GameScene::player)->SetVelo(-15, 10, 0);
		}
		break;
	case Band::STOP:
		tip->SetVelo(0, 0, 0);
		if (sendDelay == false)
		{
			delay->SetSignal(60);
			sendDelay = true;
		}
		if (delay->GetSignal())
		{
			status = LIMIT;
			sendDelay = false;
		}
		break;
	case Band::LIMIT:
		if (sendDelay == false)
		{
			delay->SetSignal(120);
			sendDelay = true;
		}
		if (delay->GetSignal())
		{
			status = REVERSE;
			sendDelay = false;
		}
		break;
	case Band::REVERSE:
		tip->m_Position.x += 60;
		break;
	}

	if (tip->m_Position.x + BLOCK_SIZE * 1.5f >= m_Position.x)
	{
		tip->SetPos(m_Position.x - BLOCK_SIZE * 2, m_Position.y, 0);
		tip->SetVelo(0, 0, 0);
		status = DEFAULT;
	}
}

void Band::Uninit()
{
	Object::Delete(tip);

	auto bufJagged = jagged;
	for (auto& obj : bufJagged)
	{
		Object::Delete(obj);
		jagged.erase(obj);
	}

	Object::Delete(delay);
}

void Band::Add(Object* _object)
{
	objects.insert(_object);
}

void Band::Remove(Object* _object)
{
	objects.erase(_object);
}

void Band::SetLength(int _length)
{
	auto bufJagged = jagged;
	for (auto& jag : bufJagged)
	{
		Object::Delete(jag);
		jagged.erase(jag);
	}

	L = _length + 1;

	tip->SetPos(m_Position.x - 60, m_Position.y, 0);
	oldPos = { m_Position.x - 60, m_Position.y, 0 };
	for (int i = 0; i < L; i++)
	{
		auto buf = Object::Create<Quad>();
		buf->SetTex("asset/Texture/Band_meter.png");
		buf->SetPos(m_Position.x + 60 * i, m_Position.y, 0);
		buf->SetScale(60, 30, 0);
		jagged.insert(buf);
	}

}

void Band::SetObject(std::string _tag)
{
	objectTag = _tag;
	ResetObject();
}

void Band::ResetObject()
{
	for (auto& obj : SceneManager::ListCreate())
	{
		if (obj->tags.SearchTag(objectTag))
		{
			Add(obj);
		}
	}
	for (auto& obj : *Scene::GetInstance()->GetObjects())
	{
		if (obj->tags.SearchTag(objectTag))
		{
			Add(obj);
		}
	}
}

std::vector<std::string> Band::GetData() const
{
	std::vector<std::string> buf;

	// オブジェクト名
	buf.push_back("Band");

	// オブジェクトの基本情報
	auto objData = Object::GetData();
	buf.insert(buf.end(), objData.begin(), objData.end());

	// 長さの情報
	buf.push_back(std::to_string(L));

	// 付属オブジェクト用タグの情報
	buf.push_back(objectTag);

	return buf;
}

bool Band::SetData(std::vector<std::string> _data)
{
	if (_data.front() == "Band")
	{
		std::vector<std::string> objBuf(7 + stoi(_data[6]));
		std::copy(_data.begin() + 1, _data.begin() + 7 + stoi(_data[6]), objBuf.begin());
		Object::SetData(objBuf);

		L = stoi(_data[7 + stoi(_data[6])]);

		objectTag = _data[8 + stoi(_data[6])];

		tip->SetScale(BLOCK_SIZE, BLOCK_SIZE, 0.0f);
		tip->moveDirection = moveDirection;
		tip->band = this;
		for (auto& tag : tags)
		{
			tip->tags.AddTag(tag);
		}


		return true;
	}
	else
	{
		return false;
	}
}