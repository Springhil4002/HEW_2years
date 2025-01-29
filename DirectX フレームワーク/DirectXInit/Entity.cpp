#include "Entity.h"

void Entity::Update()
{	
	// 加速度を速度に足す
	m_Velocity += m_Acceleration;

	// 速度が0より大きいなら
	if (m_Velocity.LengthSquared() > 0.001f)
	{
		// 元の位置保存
		auto buf = m_Position;
		// 全てのEntityを取得
		auto allEntity = Scene::GetInstance()->GetObjects<Entity>();

		// 速度を位置に足す
		m_Position.x += m_Velocity.x;
		// 衝突フラグ
		bool coll = false;
		// カウンタ
		int cnt = 0;

		for (auto& sub : allEntity)
		{
			while (Object::Collision(this, sub) && cnt < 8)
			{
				// 8回まで戻る
				m_Position.x -= m_Velocity.x / 8;
				cnt++;
			}
		}

		cnt = 0;
		m_Position.y += m_Velocity.y;
		for (auto& sub : allEntity)
		{
			while (Object::Collision(this, sub) && cnt < 8)
			{
				// 8回まで戻る
				m_Position.y -= m_Velocity.y / 8;
				cnt++;
			}
		}

		// 元の座標から速度再計算
		m_Velocity = m_Position - buf;
	}
	else
	{
		// 速度を完全に0にする
		m_Velocity = DirectX::SimpleMath::Vector3(0, 0, 0);
	}

	// 描画処理
	Quad::Update();
}

std::vector<std::string> Entity::GetData() const
{
	std::vector<std::string> buf;
	buf.push_back("Entity");
	auto objectData = Quad::GetData();
	buf.insert(buf.end(), objectData.begin(), objectData.end());
	return buf;
}

bool Entity::SetData(std::vector<std::string> _data)
{
	if (_data.front() == "Entity")
	{
		std::vector<std::string> objBuf(_data.size());
		std::copy(_data.begin() + 1, _data.end(), objBuf.begin());
		Quad::SetData(objBuf);


		return true;
	}
	else
	{
		return false;
	}
}