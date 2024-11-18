#pragma once

#include "Component.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"

//=======================================================================================
// Quadクラス
//=======================================================================================
class Quad :public Component 
{
private:
	// 描画のための情報(メッシュに関わる情報)
	IndexBuffer m_IndexBuffer;				// インデックスバッファ
	VertexBuffer<VERTEX_3D> m_VertexBuffer;	// 頂点バッファ

	// 描画のための情報(見た目に関わる部分)
	Shader m_Shader; // シェーダー
	Texture m_Texture;	// テクスチャ

public:
	// オーバーライドした関数
	void Start(const std::string& filename);	// 初期化処理
	void Update();								// 更新処理
	void Draw();								// 描画処理
};