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

// �V�[���������Ă���I�u�W�F�N�g���擾����֐�
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

// �V�[�������I�u�W�F�N�g��ǉ�����֐�
Object* Scene::AddGameObject()
{
	Object* buff = new Object();
	buff->Parent = this;
	GameObjectList.push_back(buff);
	return buff;
}
