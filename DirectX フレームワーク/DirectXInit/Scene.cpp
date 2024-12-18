#include "Scene.h"
#include "Object.h"
#include<map>

Scene* Scene::sceneInstance;
Input Scene::input;

void Scene::Input()
{
	input.Update();
}

void Scene::Draw()
{
	std::map<int, std::set<Object*>> layer;

	for (auto& obj : objectInstance)
	{
		layer[obj->layer].insert(obj);
	}

	for (auto& lay : layer)
	{
		for (auto& obj : lay.second)
		{
			obj->Draw();
		}
	}
}

void Scene::Uninit()
{
	for (auto& obj : objectInstance)
	{
		obj->Uninit();
	}
}

Scene* Scene::GetInstance()
{
	return sceneInstance;
}

std::set<Object*>* Scene::GetObjects()
{
	return &objectInstance;
}