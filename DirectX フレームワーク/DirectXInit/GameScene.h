#pragma once
#include "Scene.h"

#define OBJECT_X_VALUE (32)
#define OBJECT_Y_VALUE (18)
#define GROUND_OFFSET_X (-930.0f)
#define GROUND_OFFSET_Y (-510.0f)

class GameScene 
	: public Scene
{
private:
	Quad bg;		//背景オブジェクト
	Player player;	// プレイヤー
	std::vector<Ground*> ground;	// 地面
	Physic test;
public:
	GameScene();	//コンストラクタ(初期化処理関数)
	~GameScene();	//デストラクタ　(解放処理関数)

	//オーバーライドした関数
	void Update();	// 更新処理関数
	void Draw();	// 描画処理関数
};