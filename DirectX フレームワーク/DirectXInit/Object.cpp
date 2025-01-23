#include "Object.h"

// 今のとこ追記なし
void Object::SetPos(float _x, float _y, float _z)
{
	//座標をセットする
	m_Position.x = _x;
	m_Position.y = _y;
	m_Position.z = _z;
}
void Object::SetScale(float _x, float _y, float _z)
{
	//大きさをセットする
	m_Scale.x = _x;
	m_Scale.y = _y;
	m_Scale.z = _z;
}
void Object::SetRotation(float _x, float _y, float _z)
{
	// 角度をセットする
	m_Rotation.x = _x;
	m_Rotation.y = _y;
	m_Rotation.z = _z;
}

bool Object::SetData(std::vector<std::string> _data)
{
	if (_data[0] == "Object")
	{
		m_Position.x = stoi(_data[1]);
		m_Position.y = stoi(_data[2]);
		layer = stoi(_data[3]);
		if (_data[4] == "Tags")
		{
			int size = stoi(_data[5]);
			for (int i = 0; i < size; i++)
			{
				tags.AddTag(_data[i + 6]);
			}
		}
		else
		{
			return false;
		}

		return true;
	}
	else
	{
		return false;
	}	
}

DirectX::SimpleMath::Vector3 Object::GetPos() const
{
	return m_Position;
}

DirectX::SimpleMath::Vector3 Object::GetScale() const
{
	return m_Scale;
}

std::vector<std::string> Object::GetData() const
{
	std::vector<std::string> buf;
	buf.push_back("Object");
	buf.push_back(std::to_string(m_Position.x));
	buf.push_back(std::to_string(m_Position.y));
	buf.push_back(std::to_string(layer));
	auto tagsData = tags.GetData();
	buf.insert(buf.end(), tagsData.begin(), tagsData.end());

	return buf;
}

void Object::Delete(Object* _object)
{
	SceneManager::SetDelete(_object);
}

bool Object::Collision(Object* _object1, Object* _object2)
{
	// 自分と衝突するって何だよ
	if (_object1 == _object2)
	{
		return false;
	}
	else
	{
		// 2つの中心距離の絶対値を計算
		DirectX::SimpleMath::Vector3 distance;
		distance = _object1->m_Position - _object2->m_Position;
		distance = { abs(distance.x), abs(distance.y), 0 };

		// 2つの幅の合計を計算
		DirectX::SimpleMath::Vector3 sumScale;
		sumScale = _object1->m_Scale + _object2->m_Scale;
		sumScale /= 2.05f;

		// 幅が両方共距離より大きければ衝突
		return distance.x < sumScale.x && distance.y < sumScale.y;
	}
}