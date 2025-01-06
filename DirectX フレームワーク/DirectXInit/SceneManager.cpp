#include "SceneManager.h"
#include "TitleScene.h"
#include "HomeScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Quad.h"

Scene* SceneManager::currentScene = nullptr;
SceneManager::SCENE SceneManager::nextScene = TITLE;
bool SceneManager::changed = false;
// �ÓI�����o�[�ϐ��̒�`
SoundManager SceneManager::m_SoundManager;

void SceneManager::NewScene()
{
	if (currentScene != nullptr)
	{
		delete currentScene;
		currentScene = nullptr;
	}

	switch (nextScene) {
	case SCENE::TITLE:
		currentScene = new TitleScene();
		break;
	case SCENE::HOME_1:
		currentScene = new HomeScene();
		break;
	case SCENE::HOME_2:
		currentScene = new HomeScene();
		break;
	case SCENE::GAME:
		currentScene = new GameScene();
		break;
	case SCENE::RESULT:
		currentScene = new ResultScene();
		break;
	}
}

void SceneManager::ChangeScene(SCENE _scene)
{
	nextScene = _scene;
	changed = true;
}

void SceneManager::Init()
{
	m_SoundManager.Init();	// �T�E���h�}�l�[�W���[��������
	Quad::m_Shader.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");
	ChangeScene(TITLE);
}

void SceneManager::Update()
{
	// �V�[�����ς���Ă�����V�[���̏�����������^�C�~���O
	if (changed)
	{
		NewScene();
		currentScene->Init();
		changed = false;
	}

	// �I�u�W�F�N�g�̏������̃^�C�~���O
	//for (auto& obj : *currentScene->GetObjects())
	//{
	//	if (obj.)
	//	{
	//		obj->Init();//��ł��
	//	}
	//}

	// ���͏����̃^�C�~���O
	currentScene->Input();

	// �X�V�����̃^�C�~���O
	currentScene->Update();

	// �V�[�����ς���Ă�����V�[���̏I������������^�C�~���O
	if (changed)
	{
		currentScene->Uninit();
	}
}

void SceneManager::Draw()
{
	//���݂̃V�[���̕`��
	currentScene->Draw();
}

void SceneManager::Uninit()
{
	if (currentScene != nullptr)
	{
		delete currentScene;
	}
}
