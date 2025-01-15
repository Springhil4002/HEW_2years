#pragma once
#include "Scene.h"
#include "Enum.h"

class GameOverScene 
	: public Scene
{
private:
	int frameNum = 1;				// frameの識別用番号
public:
	static SCENE isEndSceneNum;		// 最後に終わったGameSceneを入れる変数

	GameOverScene() {};				// コンストラクタ(初期化処理)
	~GameOverScene() {};			// デストラクタ	(解放処理)

	//オーバーライドした関数
	void Init();					// 初期化処理
	void Update();					// 更新処理
};