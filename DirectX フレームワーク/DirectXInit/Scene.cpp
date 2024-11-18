#include "Scene.h"

Scene::Scene()
{
	
}

Scene::~Scene()
{

}

void Scene::Update()
{

}

void Scene::Draw()
{

}

// シーンが持っているオブジェクトを取得する関数
Object* Scene::GetGameObject()
{
	for (auto com : GameObjectList) {
		Object* buff = dynamic_cast<Object*>(com);
		if (buff != nullptr) {
			return buff;
		}
	}
	return nullptr;
}

// シーンが持つオブジェクトを追加する関数
Object* Scene::AddGameObject()
{
	Object* buff = new Object();
	buff->Parent = this;
	GameObjectList.push_back(buff);
	return buff;
}
