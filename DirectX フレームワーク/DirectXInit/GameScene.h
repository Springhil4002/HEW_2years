#pragma once
#include "Scene.h"

class GameScene 
	: public Scene
{
private:
	TestQuad BackGround;	//背景オブジェクト
public:
	GameScene();	//コンストラクタ(初期化処理関数)
	~GameScene();	//デストラクタ　(解放処理関数)

	//オーバーライドした関数
	void Update();	//更新処理関数
	void Draw();	//描画処理関数
};

