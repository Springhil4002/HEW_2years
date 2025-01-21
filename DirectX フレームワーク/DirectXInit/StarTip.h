#pragma once
#include "Quad.h"

class StarTip
	: public Quad
{
public:

	static bool geting;	// starTipの獲得フラグ
	static bool seting;	// starTipのセットフラグ

	StarTip() {}		// コンストラクタ
	~StarTip() {}		// デストラクタ

	// オーバーライドした関数
	void Init();		// 初期化処理
	void Update();		// 更新処理
};