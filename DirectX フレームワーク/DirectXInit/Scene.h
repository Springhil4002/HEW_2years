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
	static Scene* sceneInstance;	//シーンのインスタンス

	std::vector<Object*> objectInstance; //オブジェクトのインスタンス
public:
	static Input input;		//入力系インスタンス
	
	Scene(){			//コンストラクタ
		delete sceneInstance;
		sceneInstance = this;
	}

	~Scene() {			//デストラクタ
		sceneInstance = nullptr;
	}

	
	static void Input();	//入力取得処理関数
	void Draw();	//描画処理関数
	void Uninit();	//終了処理関数


	//純粋仮想関数
	virtual void Init() = 0;	//初期化処理関数
	virtual void Update() = 0;	//更新処理関数


	// 今のSceneを返すぜ
	static Scene* GetInstance();

	// 今ある全てのオブジェクトを返すぜ
	std::vector<Object*>* GetObjects();

	// その型のオブジェクトを返すぜ
	template<class T>
	std::vector<T*> GetObjects()
	{
		// 返すやつ
		std::vector<T*> ret;

		// 全オブジェクトから探そう
		for (auto& obj : objectInstance)
		{
			// ダイナミックキャストして有るならretにいれる
			T* buf = dynamic_cast<T*>(obj);
			if (buf != nullptr)
			{
				ret.push_back(buf);
			}
		}
		return ret;
	}
};