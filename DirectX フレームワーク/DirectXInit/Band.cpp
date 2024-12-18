#include "Band.h"

const int L = 5;

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
	if (pullLevel < -L * 60)
	{
		tip->SetPos(tip->GetPos().x + L * 60, tip->GetPos().y, tip->GetPos().z);
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