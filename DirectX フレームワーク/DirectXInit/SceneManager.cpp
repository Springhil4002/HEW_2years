#include "SceneManager.h"
#include "TitleScene.h"
#include "HomeScene.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "ResultScene.h"
#include "Quad.h"

Scene* SceneManager::currentScene = nullptr;
SceneManager::SCENE SceneManager::nextScene = TITLE;
bool SceneManager::changed = false;
// 静的メンバー変数の定義
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

void SceneManager::Init()
{
	m_SoundManager.Init();	// サウンドマネージャーを初期化
	Quad::m_Shader.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");
	ChangeScene(TITLE);
}

void SceneManager::Update()
{
	// シーンが変わっていたらシーンの初期化をするタイミング
	if (changed)
	{
		NewScene();
		currentScene->Init();
		changed = false;
	}

	// オブジェクトの初期化のタイミング
	//for (auto& obj : *currentScene->GetObjects())
	//{
	//	if (obj.)
	//	{
	//		obj->Init();//後でやる
	//	}
	//}

	// 入力処理のタイミング
	currentScene->Input();

	// 更新処理のタイミング
	currentScene->Update();

	// シーンが変わっていたらシーンの終了処理をするタイミング
	if (changed)
	{
		currentScene->Uninit();
	}
}

void SceneManager::Draw()
{
	//現在のシーンの描画
	currentScene->Draw();
}

void SceneManager::Uninit()
{
	if (currentScene != nullptr)
	{
		delete currentScene;
	}
}
