#include "StarTip.h"

void StarTip::Init()
{
	SetTex("asset/Texture/Band_StarTip_Clear.png");		// 画像読み込み
	SetScale(BLOCK_SIZE*6, BLOCK_SIZE*6, 0.0f);			// 大きさを設定
	layer = 1;											// レイヤーを設定
}

void StarTip::Update()
{
	Quad::Update();

	if (geting == true && seting == false) {
		SetTex("asset/Texture/Band_StarTip.png");		// 画像読み込み
		SetScale(BLOCK_SIZE * 4, BLOCK_SIZE * 4, 0.0f);	// 大きさを設定
		seting = true;
	}
}
