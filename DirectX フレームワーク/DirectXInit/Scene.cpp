#include "Scene.h"
#include "Object.h"

Scene* Scene::sceneInstance;
Input Scene::input;

void Scene::Input()
{
	input.Update();
}

void Scene::Draw()
{
	for (auto& obj : objectInstance)
	{
		obj->Draw();
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

std::vector<Object*>* Scene::GetObjects()
{
	return &objectInstance;
}