#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Object.h"
#include "TextureManager.h"

//=======================================================================================
// Quadクラス
//=======================================================================================
class Quad :public Object{
protected:
	// 描画のための情報(メッシュに関わる情報)
	IndexBuffer m_IndexBuffer;				// インデックスバッファ
	VertexBuffer<VERTEX_3D> m_VertexBuffer;	// 頂点バッファ

	// 描画のための情報(見た目に関わる部分)
	TextureManager m_Texture;	// テクスチャ

public:

	void Init(const std::string& filename);
	// オーバーライドした関数
	void Update();	// 更新処理
	void Draw();	// 描画処理
	void Uninit();	// 解放処理
};