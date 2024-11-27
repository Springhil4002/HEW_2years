#pragma once
#include "Scene.h"

#define OBJECT_VALUE (26)

class GameScene 
	: public Scene
{
private:
	Quad bg;	//背景オブジェクト
	std::vector<Ground*> ground;	// 地面
public:
	GameScene();	//コンストラクタ(初期化処理関数)
	~GameScene();	//デストラクタ　(解放処理関数)

	//オーバーライドした関数
	void Update();	// 更新処理関数
	void Draw();	// 描画処理関数
};