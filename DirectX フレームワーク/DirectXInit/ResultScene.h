#pragma once
#include "Scene.h"

#define SET_STARTIP			(3)

class ResultScene
	: public Scene
{
private:
	static int tipCount;		// bandTipの獲得数
	static int meterCount;		// 引っぱったバンドカウント
public:
	ResultScene(int _num) { Init(_num); };		//コンストラクタ(初期化処理関数)
	~ResultScene() {};							//デストラクタ　(解放処理関数)

	void Init(int _num);

	//オーバーライドした関数
	void Init() {}			// 初期化処理
	void Update();			// 更新処理関数
};

