#pragma once
#include "Scene.h"

#define SET_STARTIP			(3)
#define SET_BLOCK			(100)

class ResultScene
	: public Scene
{
private:
	static int tipCount;			// bandTipの獲得数
	static int meterCount;			// 引っぱったバンドカウント
public:
	bool drawFlag = true;			// CLEARロゴ描画フラグ
	bool drawClearFlag = false;		// CLEARロゴ描画完了フラグ	
	bool moveFlag = false;			// CLEARロゴ移動フラグ
	int count = 0;					// frameCount

	ResultScene(int _num)			//コンストラクタ(初期化処理関数)
	{ Init(_num); };		
	~ResultScene() {};				//デストラクタ　(解放処理関数)

	void Init(int _num);			// 基本的に使う初期化処理

	//オーバーライドした関数
	void Init() {}					// 初期化処理
	void Update();					// 更新処理関数

	void PullScoreUpdate();			// 引っ張った長さに応じてスコアを更新
	void CoinCounter();				// コイン獲得数UIの各桁更新処理
	void CoinGetPercent();			// コイン獲得数の割合に応じてStarTipの獲得状況の更新
	void ClearBig();				// CLEARのロゴ拡大表示
	void ClearMove();				// CLEARのロゴ縮小移動
	void ClearDraw();				// CLEARロゴの描画処理
};

