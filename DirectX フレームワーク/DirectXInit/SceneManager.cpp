#include "SceneManager.h"
#include "Scene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"

//���݂̃V�[���̏�����
Scene* SceneManager::currentScene = nullptr;

void SceneManager::ChangeScene(SCENE _scene)
{
	if (currentScene != nullptr)
	{
		currentScene = nullptr;
	}

	switch (_scene) {
	case SCENE::TITLE:
		currentScene = new TitleScene();
		break;
	case SCENE::GAME:
		currentScene = new GameScene();
		break;
	case SCENE::RESULT:
		currentScene = new ResultScene();
		break;
	default:
		break;
	}
}

void SceneManager::Update()
{
	if (currentScene)
	{
		//���݂̃V�[���̍X�V
		currentScene->Update();
	}
}

void SceneManager::Draw()
{
	if (currentScene)
	{
		//���݂̃V�[���̕`��
		currentScene->Draw();
	}
}


