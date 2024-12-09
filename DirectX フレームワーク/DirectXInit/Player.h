#pragma once
#include "Input.h"
#include "Entity.h"

class Player 
	: public Entity {
private:
	//Input input;			// 入力インスタンス
	float velocity; 		// 速度
	const float gravity;	// 重力
	const float jumpSpeed;	// ジャンプの初速度
	bool isFalling;
	bool isJumping;			// ジャンプしてるかの否かのフラグ
public:
	Player();		// コンストラクタ

	// オーバーライドした関数
	void Init();	// 初期化処理
	void Update();	// 更新処理
	//void Draw();	// 描画処理
	//void Uninit();	// 解放処理

	// プレイヤーの挙動
	void Walk();		// 左右移動(歩く)
	void Jump();		// ジャンプ
	void GrabBand();	// 結束バンドを触る(掴む)
	void PullBand();	// 結束バンドを引っ張る
};