#pragma once
#include "Scene.h"

class PlayOperateScene
	: public Scene
{
private:

public:
	PlayOperateScene();		// コンストラクタ(初期化処理)
	~PlayOperateScene();		// デストラクタ	(解放処理)

	//オーバーライドした関数
	void Init();
	void Update();		// 更新処理
};