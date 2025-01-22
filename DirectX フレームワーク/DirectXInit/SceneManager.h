#pragma once
#include "Scene.h"
#include "SoundManager.h"
#include "Enum.h"

class SceneManager
{
private:
	static Scene* currentScene;	//現在のシーン
	static bool changed;

	static std::set<Object*> createObjects;	// 生成するオブジェクト
	static std::set<Object*> deleteObjects;	// 削除するオブジェクト


	static void NewScene(int _num);
public:
	static int num;
	static SCENE nextScene;
	static SoundManager m_SoundManager;	// シーンマネージャーのインスタンス
	SceneManager() {}		//コンストラクタ
	~SceneManager() {}		//デストラクタ

	static void Init();		//初期化処理関数
	static void Update();	//更新処理関数
	static void Draw();		//描画処理関数
	static void Uninit();	//解放処理関数

	//現在のシーンを切り替える処理関数
	static void ChangeScene(SCENE _scene, int _num = 0);

	// 生成するオブジェクトを作成
	template<class T>
	static T* SetCreate()
	{
		T* buf = new T;
		createObjects.insert(buf);
		return buf;
	}

	// 削除するオブジェクトを登録
	static void SetDelete(Object* _object);

	static std::set<Object*> ListCreate() { return createObjects; }
	static std::set<Object*> ListDelete() { return deleteObjects; }

};