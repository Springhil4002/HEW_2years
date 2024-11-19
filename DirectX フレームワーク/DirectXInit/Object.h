#pragma once
#include <simpleMath.h>
#include "Component.h"
#include "Scene.h"

class Component;

class Object {
private:
	// SRT���(�p�����)
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
public:
	std::string name;
	std::vector<Component*> ComponentList;

	// �e��Z�b�^�[
	void SetPos(float _x, float _y, float _z);				//���W���Z�b�g
	void SetRotation(float _x, float _y, float _z);			//�p�x���Z�b�g
	void SetScale(float _x, float _y, float _z);			//�傫�����Z�b�g

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

	// �I�u�W�F�N�g�������Ă���R���|�[�l���g�̎擾����֐�
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

	// �I�u�W�F�N�g�����R���|�[�l���g��ǉ�
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