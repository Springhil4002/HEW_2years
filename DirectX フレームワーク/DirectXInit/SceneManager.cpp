#include "SceneManager.h"
#include "TitleScene.h"
#include "HomeScene.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "ResultScene.h"
#include "Quad.h"
#include "MapEditor.h"

Scene* SceneManager::currentScene = nullptr;
bool SceneManager::changed = false;
std::set<Object*> SceneManager::createObjects;
std::set<Object*> SceneManager::deleteObjects;
SCENE SceneManager::nextScene = TITLE;
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
		currentScene = new HomeScene(1);
		break;
	case SCENE::HOME_2:
		currentScene = new HomeScene(2);
		break;
	case SCENE::GAME_1:
		currentScene = new GameScene(1);
		break;
	case SCENE::GAME_2:
		currentScene = new GameScene(2);
		break;
	case SCENE::GAME_3:
		currentScene = new GameScene(3);
		break;
	case SCENE::GAME_4:
		currentScene = new GameScene(4);
		break;
	case SCENE::GAME_5:
		currentScene = new GameScene(5);
		break;
	case SCENE::GAME_6:
		currentScene = new GameScene(6);
		break;
	case SCENE::GAME_7:
		currentScene = new GameScene(7);
		break;
	case SCENE::GAME_8:
		currentScene = new GameScene(8);
		break;
	case SCENE::GAMEOVER:
		currentScene = new GameOverScene();
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

void SceneManager::SetDelete(Object* _object)
{
	deleteObjects.insert(_object);
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

	// �I�u�W�F�N�g�̐����Ə������̃^�C�~���O
	if (!createObjects.empty())
	{
		auto buf = createObjects;
		for (auto& obj : buf)
		{
			obj->Init();
			currentScene->GetObjects()->insert(obj);
			createObjects.erase(obj);
		}
	}

	// ���͏����̃^�C�~���O
	currentScene->Input();

	// �X�V�����̃^�C�~���O
	currentScene->Update();

	if (!deleteObjects.empty())
	{
		auto buf = deleteObjects;
		for (auto& obj : buf)
		{
			obj->Uninit();
			currentScene->GetObjects()->erase(obj);
			deleteObjects.erase(obj);
			delete obj;
		}
	}

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
