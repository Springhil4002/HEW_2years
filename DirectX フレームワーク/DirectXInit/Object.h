#pragma once
#include <simpleMath.h>
#include "Component.h"
#include "Scene.h"

class Component;

class Object {
private:
	// SRT情報(姿勢情報)
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
public:
	std::string name;
	std::vector<Component*> ComponentList;

	// 各種セッター
	void SetPos(float _x, float _y, float _z);				//座標をセット
	void SetRotation(float _x, float _y, float _z);			//角度をセット
	void SetScale(float _x, float _y, float _z);			//大きさをセット

	Object(const std::string& _name):name(_name) {}
	~Object() {
		for (auto com : ComponentList) {
			delete com;
		}
	}
	
	void Update()
	{
		auto buff = ComponentList;
		for (auto com : buff) {
			com->Update();
		}
	}

	void Draw()
	{
		for (auto com : ComponentList) {
			com->Draw();
		}
	}

	// オブジェクトが持っているコンポーネントの取得する関数
	template<class T>
	T* GetComponent()
	{
		for (auto com : ComponentList) {
			T* buff = dynamic_cast<T*>(com);
			if (buff != nullptr) {
				return buff;
			}
		}
		return nullptr;
	}

	// オブジェクトが持つコンポーネントを追加
	template<class T>
	T* AddComponent()
	{
		T* buff = new T();
		buff->Parent = this;
		ComponentList.push_back(buff);
		buff->Start();
		return buff;
	}
};