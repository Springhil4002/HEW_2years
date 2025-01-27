#pragma once
#include "Scene.h"

class HomeScene
	: public Scene
{
private:
	int homeSceneNum = 0;	// HomeSceneの切り替え用の番号
	int frameNum = 0;		// frameの識別用番号
public:
	bool fadeOut_Start = false;		// フェード開始フラグ
	bool fadeOut_End = false;		// フェード終了フラグ

	HomeScene(int _num);	// コンストラクタ(初期化処理)
	~HomeScene() {};		// デストラクタ	(解放処理)

	void Init(int _num);	// 基本的に初期化処理はこっち使う

	//オーバーライドした関数
	void Init() {};			// 初期化処理
	void Update();			// 更新処理

	void Frame_Input();		// フレーム移動入力処理
	void Frame_Move();		// フレーム移動処理
	void ChangeHome();		// HomwScene切り替え処理
	void Fade_In();			// フェードイン処理		(明るくなる)
	void Fade_Out();		// フェードアウト処理	(暗くなる)

	// ゲッター・セッター
	int GetFrameNum() { return frameNum; }
	void SetFrameNum(int _frameNum) { frameNum = _frameNum; }

	int GetHomeSceneNum() { return homeSceneNum; }
	void SetHomeSceneNum(int _homeSceneNum) { homeSceneNum = _homeSceneNum; }
};