#pragma once
#include "Scene.h"

class ResultScene
	: public Scene
{
private:
	//Quad bg;	//背景オブジェクト
public:
	ResultScene();	//コンストラクタ(初期化処理関数)
	~ResultScene();	//デストラクタ　(解放処理関数)

	//オーバーライドした関数
	void Init();
	void Update();	// 更新処理関数
	//void Draw();	// 描画処理関数
};

