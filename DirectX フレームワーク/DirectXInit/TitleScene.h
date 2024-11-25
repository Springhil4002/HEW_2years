#pragma once
#include "Scene.h"

class TitleScene 
	: public Scene
{
private:
	Quad bg;	// 背景オブジェクト
	//std::vector <std::unique_ptr<Object>>objects;	// オブジェクト配列
public:
	TitleScene();		// コンストラクタ(初期化処理)
	~TitleScene();		// デストラクタ	(解放処理)

	//オーバーライドした関数
	void Update();		// 更新処理
	void Draw();		// 描画処理
};