#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Object.h"
#include "TextureManager.h"

//=======================================================================================
// Quadクラス
//=======================================================================================
class Quad :public Object{
protected:
	enum MOVEDIRECTION {
		LEFT,
		RIGHT
	};
	// 描画のための情報(メッシュに関わる情報)
	IndexBuffer m_IndexBuffer;				// インデックスバッファ
	VertexBuffer<VERTEX_3D> m_VertexBuffer;	// 頂点バッファ

	// 描画のための情報(見た目に関わる部分)
	TextureManager m_Texture;	// テクスチャ

	MOVEDIRECTION moveDirection = RIGHT;

private:
	MOVEDIRECTION old = moveDirection;

public:
	// 描画の為の情報（見た目に関わる部分）
	static Shader m_Shader; // シェーダー

	// オーバーライドした関数
	void Init();	// 初期化処理
	void Update();	// 更新処理
	void Draw();	// 描画処理
	void Uninit();	// 解放処理

	void SetTex(const std::string& filename);
};