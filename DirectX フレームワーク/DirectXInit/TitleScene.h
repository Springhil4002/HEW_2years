#pragma once
#include "Scene.h"

class TitleScene 
	: public Scene
{
private:
	int frameNum = 1;		// frameの識別用番号
public:
	TitleScene() {};		// コンストラクタ(初期化処理)
	~TitleScene() {};		// デストラクタ	(解放処理)

	//オーバーライドした関数
	void Init();			// 初期化処理
	void Update();			// 更新処理
};