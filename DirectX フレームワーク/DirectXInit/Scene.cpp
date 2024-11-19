#include "Scene.h"

Scene::Scene()
{
	
}

Scene::~Scene()
{
	for (auto* obj : GameObjectList) {
		delete obj;
	}
}

void Scene::Update()
{

}

void Scene::Draw()
{

}

// シーンが持っているオブジェクトを取得する関数
Object* Scene::GetGameObject(const std::string& _name)
{
	for (Object* GameObject : GameObjectList)
	{
		if (GameObject->name == _name)
		{
			return GameObject;
		}
	}
	return nullptr;
}

// シーンが持つオブジェクトを追加する関数
void Scene::AddGameObject(std::string _name)
{
	Object* buff = new Object(_name);
	buff->name = _name;
	GameObjectList.push_back(buff);
}
