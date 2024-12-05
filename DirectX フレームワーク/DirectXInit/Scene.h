#pragma once
#include <stdio.h>
#include <vector>
#include "input.h"

#define BACKGROUND_X (1920)
#define BACKGROUND_Y (1080)
#define BLOCK_SIZE	(60.0f)

class Object;

class Scene
{
protected:
	static Scene* sceneInstance;	//�V�[���̃C���X�^���X
	static Input input;		//���͌n�C���X�^���X

	std::vector<Object*> objectInstance; //�I�u�W�F�N�g�̃C���X�^���X
public:
	Scene(){			//�R���X�g���N�^
		delete sceneInstance;
		sceneInstance = this;
	}

	~Scene() {			//�f�X�g���N�^
		sceneInstance = nullptr;
	}

	
	static void Input();	//���͎擾�����֐�
	void Draw();	//�`�揈���֐�
	void Uninit();	//�I�������֐�


	//�������z�֐�
	virtual void Init() = 0;	//�����������֐�
	virtual void Update() = 0;	//�X�V�����֐�


	// ����Scene��Ԃ���
	static Scene* GetInstance();

	// ������S�ẴI�u�W�F�N�g��Ԃ���
	std::vector<Object*>* GetObjects();

	// ���̌^�̃I�u�W�F�N�g��Ԃ���
	template<class T>
	std::vector<T*> GetObjects()
	{
		// �Ԃ����
		std::vector<T*> ret;

		// �S�I�u�W�F�N�g����T����
		for (auto& obj : objectInstance)
		{
			// �_�C�i�~�b�N�L���X�g���ėL��Ȃ�ret�ɂ����
			T* buf = dynamic_cast<T*>(obj);
			if (buf != nullptr)
			{
				ret.push_back(buf);
			}
		}
		return ret;
	}
};