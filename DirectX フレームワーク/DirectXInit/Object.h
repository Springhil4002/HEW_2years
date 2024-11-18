#pragma once
#include <simpleMath.h>
#include "Component.h"

class Component;

class Object {
public:
	Scene* Parent;
	std::list<Component*> ComponentList;

	Object() {}
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