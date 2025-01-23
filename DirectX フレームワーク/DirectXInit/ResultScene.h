#pragma once
#include "Scene.h"

#define SET_STARTIP			(3)
#define SET_BLOCK			(100)

class ResultScene
	: public Scene
{
private:
	static int tipCount;		// bandTipの獲得数
	static int meterCount;		// 引っぱったバンドカウント
public:
	bool flag = false;			// フラグ設定フラグ
	bool Check_Clear = false;	// CLEARロゴ描画完了フラグ
	ResultScene(int _num) { Init(_num); };		//コンストラクタ(初期化処理関数)
	~ResultScene() {};							//デストラクタ　(解放処理関数)

	void Init(int _num);

	//オーバーライドした関数
	void Init() {}			// 初期化処理
	void Update();			// 更新処理関数

	void PullScoreUpdate();	// 引っ張った長さに応じてスコアを更新
	void CoinCounter();		// コイン獲得数UIの各桁更新処理
	void CoinGetPercent();	// コイン獲得数の割合に応じてStarTipの獲得状況の更新
	void ClearDraw();		// CLEARのロゴ表示演出
	void ClearMove();		// CLEARのロゴ移動
};

