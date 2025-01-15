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

	void Frame_Input();		// フレーム移動入力処理
	void Frame_Move();		// フレーム移動処理

	// ゲッター・セッター
	int GetFrameNum() { return frameNum; }
	void SetFrameNum(int _frameNum) { frameNum = _frameNum; }
};