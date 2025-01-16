#include "Band.h"


void Band::Init()
{
	// 先端の初期設定
	tip->SetTex("asset/Texture/explotion.png");
	tip->SetPos(m_Position.x - 60, m_Position.y, 0);
	oldPos = { m_Position.x - 60, m_Position.y, 0 };
	tip->SetScale(10, 10, 0);

	for (int i = 0; i < L; i++)
	{
		auto buf = Object::Create<Quad>();
		buf->SetTex("asset/Texture/ground.png");
		buf->SetPos(m_Position.x + 60 * i, m_Position.y, 0);
		buf->SetScale(60, 30, 0);
		jagged.insert(buf);
	}
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

	for (auto& obj : objects)
	{
		auto temp = obj->GetPos() + differencial;
		obj->SetPos(temp.x, temp.y, temp.z);
	}

	oldPos = tip->GetPos();
	pullLevel += differencial.x;
	tip->SetPullLeveL(pullLevel);

	if (!tip->isGrabing)
	{
		if ((int)tip->GetPos().x % 60 < 30)
		{
			tip->SetPos((int)tip->GetPos().x / 60 * 60 - 30, tip->GetPos().y, 0);
			tip->SetVelo(0, 0, 0);
		}
	}

	if (pullLevel < -(L - 1) * 60)
	{
		tip->SetPos(tip->GetPos().x + (L - 1) * 60, tip->GetPos().y, 0);
	}
}

void Band::Uninit()
{
	for (auto& obj : jagged)
		Object::Delete(obj);
}

void Band::Add(Object* _object)
{
	objects.insert(_object);
}

void Band::Remove(Object* _object)
{
	objects.erase(_object);
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

	// 付属するオブジェクトの数
	buf.push_back(std::to_string(objects.size()));

	// 付属オブジェクトの情報
	for (auto& obj : objects)
	{
		objData = obj->GetData();
		buf.insert(buf.end(), objData.begin(), objData.end());
	}
	return buf;
}

bool Band::SetData(std::vector<std::string> _data)
{

	return true;
}