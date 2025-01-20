#pragma once
#include "Quad.h"

class CoinNum
	: public Quad
{
public:
	CoinNum() {}			// コンストラクタ
	~CoinNum() {}			// デストラクタ

	// オーバーライドした関数
	void Init();		// 初期化処理
	void Update();		// 更新処理
};