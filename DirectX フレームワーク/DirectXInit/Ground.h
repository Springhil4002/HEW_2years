#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Quad.h"
#include "TextureManager.h"

//=======================================================================================
// Groundクラス
//=======================================================================================
class Ground :public Quad {
public:
	// オーバーライドした関数
	void Init();	// 初期化処理
	//void Update();	// 更新処理
	//void Draw();	// 描画処理
	//void Uninit();	// 解放処理
};