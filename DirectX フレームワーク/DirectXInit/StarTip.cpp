#include "StarTip.h"

bool StarTip::geting = false;		// starTipの獲得フラグ
bool StarTip::seting = false;		// starTipのテクスチャセットフラグ

void StarTip::Init()
{
	SetTex("asset/Texture/Band_StarTip_Clear.png");		// 画像読み込み
	SetScale(BLOCK_SIZE*2, BLOCK_SIZE*2, 0.0f);			// 大きさを設定
}

void StarTip::Update()
{
	Quad::Update();

	if (geting == true && seting==false) {
		SetTex("asset/Texture/Band_StarTip.png");		// 画像読み込み
		seting = false;
	}
}
