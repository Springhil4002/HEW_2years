#pragma once
#include "Scene.h"
#include "Player.h"

#define OBJECT_X_VALUE		(32)
#define OBJECT_Y_VALUE		(18)
#define GROUND_OFFSET_X		(-930.0f)
#define GROUND_OFFSET_Y		(-510.0f)
#define SCENE_ENUM_OFFSET	(3)

class Goal;
class GameScene : public Scene
{
private:
	int gameSceneNum;				// GameScene(ステージ)の識別用番号
	static int allBandTipCount;		// bandTipの総数
public:
	bool fadeOut_Start = false;		// フェード開始フラグ
	bool fadeOut_End = false;		// フェード終了フラグ
	static int bandTipCount;		// bandTipの獲得数
	static Player* player;

	GameScene(int _num)				//コンストラクタ
	{ Init(_num); };	
	~GameScene() {};				//デストラクタ

	void Init(int _num);			// 基本的に初期化はこっち使う
	void Fade_In();					// フェードイン処理		(明るくなる)
	void Fade_Out();				// フェードアウト処理	(暗くなる)
	void RetryGame();				// ゲーム中のリトライ機能

	//オーバーライドした関数
	void Init() {};					// 初期化処理関数
	void Update();					// 更新処理関数

	// ゲッター・セッター
	int GetGameSceneNum() { return gameSceneNum; }
	void SetGameSceneNum(int _gameSceneNum) { gameSceneNum = _gameSceneNum; }

	static int GetAllBandTipCount() { return allBandTipCount; }
	static void SetAllBandTipCount(int _allBandTipCount) { allBandTipCount = _allBandTipCount; }

	void CoinCounter();			// コイン獲得数UIの各桁更新処理
	void FallIsPlayer();		// playerの落下判定処理と遷移処理
};