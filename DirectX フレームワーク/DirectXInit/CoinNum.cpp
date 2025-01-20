#include "CoinNum.h"

void CoinNum::Init()
{
	SetTex("asset/Texture/Number.png", 10, 1, 0, 0);	// ‰æ‘œ“Ç‚İ‚İ
	SetScale(50.0f, 100.0f, 0.0f);						// ‘å‚«‚³‚ğİ’è
}

void CoinNum::Update()
{
	Quad::Update();
}


