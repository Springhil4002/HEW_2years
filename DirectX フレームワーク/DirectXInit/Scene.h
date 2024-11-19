#pragma once
#include <stdio.h>
#include "input.h"
#include "Object.h"
#include "TestQuad.h"

class Scene
{
protected:
	Input input;		//入力系インスタンス
public:
	Scene();			//コンストラクタ(初期化処理関数)
	virtual ~Scene();	//デストラクタ	(解放処理関数)

	//純粋仮想関数
	virtual void Update() = 0;	//更新処理関数
	virtual void Draw() = 0;	//描画処理関数	

	// オブジェクトを管理するリスト
	std::list<Object*>GameObjectList;
	// オブジェクトを取得する関数
	Object* GetGameObject();
	Object* AddGameObject();
};