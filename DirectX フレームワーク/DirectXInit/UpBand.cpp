#include "UpBand.h"
#include "GameScene.h"
#include "Ground.h"
#include "Band.h"
#define PIE (3.14159265)

void UpBand::Init()
{
	SetTex("asset/Texture/Band_Block.png");
	SetScale(60, 60, 0);

	// 先端の初期設定
	tip->SetTex("asset/Texture/Band_Tip.png");
	tip->SetPos(m_Position.x, m_Position.y + BLOCK_SIZE, 0);
	jagged.insert(tip);


	for (int i = 0; i < L; i++)
	{
		auto jaggedBuf = Object::Create<Quad>();
		jaggedBuf->SetTex("asset/Texture/Band_meter.png");
		jaggedBuf->SetPos(m_Position.x, m_Position.y - 60 * i, 0);
		jaggedBuf->SetRotation(0, 0, PIE / 2);
		jaggedBuf->SetScale(60, 30, 0);
		jaggedBuf->layer = layer - 1;
		jagged.insert(jaggedBuf);
	}

	ResetObject();

	oldPos = m_Position;
}

void UpBand::Update()
{	
	auto d = m_Position - oldPos;
	for (auto& obj : jagged)
	{
		auto temp = obj->GetPos();
		obj->SetPos(temp.x + d.x, temp.y + d.y, 0);
	}
	for (auto& obj : objects)
	{
		auto temp = obj->GetPos();
		obj->SetPos(temp.x + d.x, temp.y + d.y, 0);
	}
	oldPos = m_Position;

	bool moveFlg = false;
	if (GameScene::player)
	{
		if (GameScene::player->GetPos().y > m_Position.y)
		{
			if (Scene::input.GetKeyPress(VK_E))
			{
				for (auto& jag : jagged)
				{
					if (Object::Collision(GameScene::player, jag))
					{
						moveFlg = true;
						break;
					}
				}
			}
		}
	}
	
	if (moveFlg)
	{		
		// 位置の調整
		const float differencial = 1.0f;
		pullLevel += differencial;
		for (auto& obj : jagged)
		{
			auto temp = obj->GetPos();
			obj->SetPos(temp.x, temp.y + differencial, temp.z);
		}

		for (auto& obj : objects)
		{
			auto temp = obj->GetPos();
			obj->SetPos(temp.x, temp.y + differencial, temp.z);
		}

	}
	
	if (!(Scene::input.GetKeyPress(VK_E)))
	{
		pullLevel = (int)(pullLevel + 30) / 60 * 60;
		// 位置の調整
		for (auto& obj : jagged)
		{
			auto temp = obj->GetPos();
			if (temp.y > 0)
			{
				obj->SetPos(temp.x, (int)temp.y / 60 * 60 + 30, temp.z);
			}
			else
			{
				obj->SetPos(temp.x, (int)temp.y / 60 * 60 - 30, temp.z);
			}
		}

		for (auto& obj : objects)
		{
			auto temp = obj->GetPos();
			if (temp.y > 0)
			{
				obj->SetPos(temp.x, (int)temp.y / 60 * 60 + 30, temp.z);
			}
			else
			{
				obj->SetPos(temp.x, (int)temp.y / 60 * 60 - 30, temp.z);
			}
		}
	}

	bool flg = false;
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
			if (flg)
				break;
			for (auto& col : Scene::GetInstance()->GetObjects<Band>())
			{
				if (Object::Collision(obj, col))
				{
					flg = true;
					break;
				}
			}
			if (flg)
				break;
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

	// 位置戻す
	if (flg)
	{
		for (auto& obj : jagged)
		{
			auto temp = obj->GetPos();
			obj->SetPos(temp.x, temp.y - pullLevel, temp.z);
		}

		for (auto& obj : objects)
		{
			auto temp = obj->GetPos();
			obj->SetPos(temp.x, temp.y - pullLevel, temp.z);
		}

		pullLevel = 0;
	}
}

void UpBand::Uninit()
{
	Object::Delete(tip);

	auto bufJagged = jagged;
	for (auto& obj : bufJagged)
	{
		Object::Delete(obj);
		jagged.erase(obj);
	}

	//Object::Delete(delay);
}

void UpBand::Add(Object* _object)
{
	objects.insert(_object);
}

void UpBand::Remove(Object* _object)
{
	objects.erase(_object);
}

void UpBand::SetLength(int _length)
{
	auto bufJagged = jagged;
	for (auto& jag : bufJagged)
	{
		Object::Delete(jag);
		jagged.erase(jag);
	}

	L = _length;

	pullLevel = 0;
	for (int i = 0; i < L; i++)
	{
		auto buf = Object::Create<Quad>();
		buf->SetTex("asset/Texture/Band_meter.png");
		buf->SetPos(m_Position.x + 60 * i, m_Position.y, 0);
		buf->SetScale(60, 30, 0);
		jagged.insert(buf);
	}

}

void UpBand::SetObject(std::string _tag)
{
	objectTag = _tag;
	ResetObject();
}

void UpBand::ResetObject()
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

	for (auto& tag : tags)
	{
		for (auto& obj : objects)
		{
			if (obj->tags.SearchTag(tag))
			{
				obj->tags.RemoveTag(tag);
			}
		}
	}
}

std::vector<std::string> UpBand::GetData() const
{
	std::vector<std::string> buf;

	// オブジェクト名
	buf.push_back("UpBand");

	// オブジェクトの基本情報
	auto objData = Object::GetData();
	buf.insert(buf.end(), objData.begin(), objData.end());

	// 長さの情報
	buf.push_back(std::to_string(L));

	// 付属オブジェクト用タグの情報
	buf.push_back(objectTag);

	return buf;
}

bool UpBand::SetData(std::vector<std::string> _data)
{
	if (_data.front() == "UpBand")
	{
		std::vector<std::string> objBuf(7 + stoi(_data[6]));
		std::copy(_data.begin() + 1, _data.begin() + 7 + stoi(_data[6]), objBuf.begin());
		Object::SetData(objBuf);

		L = stoi(_data[7 + stoi(_data[6])]);

		objectTag = _data[8 + stoi(_data[6])];

		tip->SetRotation(0, 0, -PIE / 2);
		tip->SetScale(BLOCK_SIZE, BLOCK_SIZE, 0.0f);
		//for (auto& tag : tags)
		//{
		//	tip->tags.AddTag(tag);
		//}

		return true;
	}
	else
	{
		return false;
	}
}