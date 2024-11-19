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

// �V�[���������Ă���I�u�W�F�N�g���擾����֐�
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

// �V�[�������I�u�W�F�N�g��ǉ�����֐�
void Scene::AddGameObject(std::string _name)
{
	Object* buff = new Object(_name);
	buff->name = _name;
	GameObjectList.push_back(buff);
}
