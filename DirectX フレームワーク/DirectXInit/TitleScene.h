#pragma once
#include "Scene.h"

class TitleScene 
	: public Scene
{
private:
	int frameNum = 1;				// frameの識別用番号
public:
	bool fadeOut_Start = false;		// フェード開始フラグ
	bool fadeOut_End = false;		// フェード終了フラグ

	TitleScene() {};				// コンストラクタ(初期化処理)
	~TitleScene() {};				// デストラクタ	(解放処理)

	//オーバーライドした関数
	void Init();					// 初期化処理
	void Update();					// 更新処理

	void Frame_Input();				// フレーム移動入力処理
	void Frame_Move();				// フレーム移動処理
	void Fade_In();					// フェードイン処理		(明るくなる)
	void Fade_Out();				// フェードアウト処理	(暗くなる)

	// ゲッター・セッター
	int GetFrameNum() { return frameNum; }
	void SetFrameNum(int _frameNum) { frameNum = _frameNum; }
};