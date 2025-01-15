#pragma once
#include "Scene.h"

class ResultScene
	: public Scene
{
private:
	
public:
	ResultScene() {};		//コンストラクタ(初期化処理関数)
	~ResultScene() {};		//デストラクタ　(解放処理関数)

	//オーバーライドした関数
	void Init();			// 初期化処理
	void Update();			// 更新処理関数
};

