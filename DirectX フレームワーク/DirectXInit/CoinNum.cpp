#include "CoinNum.h"

void CoinNum::Init()
{
	SetTex("asset/Texture/Number.png", 10, 1, 0, 0);	// 画像読み込み
	SetScale(50.0f, 100.0f, 0.0f);						// 大きさを設定
}

void CoinNum::Update()
{
	Quad::Update();
}


