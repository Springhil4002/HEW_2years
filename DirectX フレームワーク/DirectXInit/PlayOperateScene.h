#pragma once
#include "Scene.h"

class PlayOperateScene
	: public Scene
{
private:
	// 特になし
public:
	bool fadeOut_Start = false;		// フェード開始フラグ
	bool fadeOut_End = false;		// フェード終了フラグ

	PlayOperateScene() {};			// コンストラクタ(初期化処理)
	~PlayOperateScene() {};			// デストラクタ	(解放処理)

	void Back_ToTitle();			// タイトルに戻る
	void Fade_In();					// フェードイン処理		(明るくなる)
	void Fade_Out();				// フェードアウト処理	(暗くなる)

	//オーバーライドした関数
	void Init();					// 初期化処理
	void Update();					// 更新処理
};