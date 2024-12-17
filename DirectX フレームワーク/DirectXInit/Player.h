#pragma once
#include "Input.h"
#include "Entity.h"
#include "SceneManager.h"

class Player : public Entity {
private:
	enum STATE
	{
		FLYING,
		ONGROUND,
		FALLING
	};

	enum MOVESTATE
	{
		STOP,
		MOVE
	};

	enum GRABSTATE
	{
		DEFAULT,
		GRAB
	};

	float velocity; 		// 速度
	const float gravity;	// 重力
	const float jumpSpeed;	// ジャンプの初速度
	bool isFalling;			// 落ちてるかのフラグ
	bool isJumping;			// ジャンプしてるかの否かのフラグ
	bool isGrabing;			// 引っ張ってるかのフラグ
	bool isMoving;

	STATE state;
	MOVESTATE groundState;
	GRABSTATE grabState;

	public:
	Player();		// コンストラクタ

	// オーバーライドした関数
	void Init();	// 初期化処理
	void Update();	// 更新処理

	// プレイヤーの挙動
	void State();		// 状態遷移
	void Walk();		// 左右移動(歩く)
	void Jump();		// ジャンプ
	void Resist();		// 抵抗
	void GrabBand();	// 結束バンドを触る(掴む)
	void PullBand();	// 結束バンドを引っ張る
};