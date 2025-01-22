#pragma once
#include "Quad.h"

class StarTip
	: public Quad
{
private:
	bool geting = false;	// starTipの獲得フラグ
	bool seting = false;	// starTipのテクスチャセットフラグ
public:
	StarTip() {}		// コンストラクタ
	~StarTip() {}		// デストラクタ

	// オーバーライドした関数
	void Init();		// 初期化処理
	void Update();		// 更新処理

	// ゲッター・セッター関係
	// starTipの獲得フラグのゲッター・セッター
	bool GetGeting() { return geting; }
	void SetGeting(bool _geting) {geting = _geting; }

	// starTipのテクスチャセットフラグのゲッター・セッター関係
	bool GetSeting() { return seting; }
	void SetSeting(bool _seting) { seting = _seting; }
};