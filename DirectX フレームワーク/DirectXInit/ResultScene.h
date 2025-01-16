#pragma once
#include "Scene.h"

#define OBJECT_X_VALUE		(64)
#define OBJECT_Y_VALUE		(18)
#define GROUND_OFFSET_X		(-1890.0f)
#define GROUND_OFFSET_Y		(-510.0f)

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

