#include "StarTip.h"

void StarTip::Init()
{
	SetTex("asset/Texture/Band_StarTip_Clear.png");		// ‰æ‘œ“Ç‚İ‚İ
	SetScale(BLOCK_SIZE*6, BLOCK_SIZE*6, 0.0f);			// ‘å‚«‚³‚ğİ’è
	layer = 1;											// ƒŒƒCƒ„[‚ğİ’è
}

void StarTip::Update()
{
	Quad::Update();

	if (geting == true && seting == false) {
		SetTex("asset/Texture/Band_StarTip.png");		// ‰æ‘œ“Ç‚İ‚İ
		SetScale(BLOCK_SIZE * 4, BLOCK_SIZE * 4, 0.0f);	// ‘å‚«‚³‚ğİ’è
		seting = true;
	}
}
