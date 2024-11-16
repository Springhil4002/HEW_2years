#pragma once
#include "Scene.h"

class TitleScene 
	: public Scene
{
private:
	TestQuad BackGround;	//背景オブジェクト
public:
	TitleScene();		//コンストラクタ(初期化処理)
	~TitleScene();		//デストラクタ	(解放処理)

	//オーバーライドした関数
	void Update();		//更新処理
	void Draw();		//描画処理
};