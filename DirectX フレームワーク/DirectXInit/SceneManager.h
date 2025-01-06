#pragma once
#include "Scene.h"
#include "SoundManager.h"

class SceneManager
{
public:
	//列挙型
	enum SCENE {
		TITLE,
		HOME_1,
		HOME_2,
		GAME,
		RESULT
	};

private:	
	static Scene* currentScene;	//現在のシーン
	static SCENE nextScene;
	static bool changed;
	static void NewScene();
public:
	static SoundManager m_SoundManager;	// シーンマネージャーのインスタンス
	SceneManager() {}		//コンストラクタ
	~SceneManager() {}		//デストラクタ

	static void Init();		//初期化処理関数
	static void Update();	//更新処理関数
	static void Draw();		//描画処理関数
	static void Uninit();	//解放処理関数

	static void ChangeScene(SCENE _scene);	//現在のシーンを切り替える処理関数
};