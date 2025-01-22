#pragma once
#include "Scene.h"
#include "SoundManager.h"
#include "Enum.h"

class SceneManager
{
private:
	static Scene* currentScene;	//���݂̃V�[��
	static bool changed;

	static std::set<Object*> createObjects;	// ��������I�u�W�F�N�g
	static std::set<Object*> deleteObjects;	// �폜����I�u�W�F�N�g


	static void NewScene(int _num);
public:
	static int num;
	static SCENE nextScene;
	static SoundManager m_SoundManager;	// �V�[���}�l�[�W���[�̃C���X�^���X
	SceneManager() {}		//�R���X�g���N�^
	~SceneManager() {}		//�f�X�g���N�^

	static void Init();		//�����������֐�
	static void Update();	//�X�V�����֐�
	static void Draw();		//�`�揈���֐�
	static void Uninit();	//��������֐�

	//���݂̃V�[����؂�ւ��鏈���֐�
	static void ChangeScene(SCENE _scene, int _num = 0);

	// ��������I�u�W�F�N�g���쐬
	template<class T>
	static T* SetCreate()
	{
		T* buf = new T;
		createObjects.insert(buf);
		return buf;
	}

	// �폜����I�u�W�F�N�g��o�^
	static void SetDelete(Object* _object);

	static std::set<Object*> ListCreate() { return createObjects; }
	static std::set<Object*> ListDelete() { return deleteObjects; }

};