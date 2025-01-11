#pragma once
#include "Scene.h"
#include "Enum.h"

class GameOverScene 
	: public Scene
{
private:
	//Quad bg;	// 背景オブジェクト
	//std::vector <std::unique_ptr<Object>>objects;	// オブジェクト配列
	int frameNum = 1;
public:

	static SCENE isEndSceneNum;

	GameOverScene();		// コンストラクタ(初期化処理)
	~GameOverScene();		// デストラクタ	(解放処理)

	//オーバーライドした関数
	void Init();		// 初期化処理
	void Update();		// 更新処理
	//void Draw();		// 描画処理
};