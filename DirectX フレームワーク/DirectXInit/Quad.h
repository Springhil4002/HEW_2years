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

	int splitX = 1;
	int splitY = 1;
	int numU = 0;
	int numV = 0;

	//色
	DirectX::SimpleMath::Color color = { 1.0f,1.0f,1.0f,1.0f };
public:
	// 描画の為の情報（見た目に関わる部分）
	static Shader m_Shader; // シェーダー
	
	Quad() {}
	~Quad() {}

	// オーバーライドした関数
	void Init();	// 初期化処理
	void Update();	// 更新処理
	void Draw();	// 描画処理
	void Uninit();	// 解放処理

	// 画像読み込み
	// ※第一引数:画像名、第二引数:横の分割数、第三引数:縦の分割数、第四引数:横から何番目、第五引数:縦から何番目
	// 　第六引数:色情報(赤)、第六引数:色情報(緑)、第六引数:色情報(青)、第六引数:色情報(アルファ値・透明度)
	void SetTex(const std::string& filename,
		int _splitX = 1, int _splitY = 1, int _numU = 0, int _numV = 0,
		float _r = 1.0f, float _g = 1.0f, float _b = 1.0f, float _a = 1.0f);

	// ゲッター・セッター

	// splitX・splitY関係
	int GetSplitX() { return splitX; }
	int GetSplitY() { return splitY; }
	void SetSplitX(int _splitX) { splitX = _splitX; }
	void SetSplitY(int _splitY) { splitY = _splitY; }

	// numU・numV関係
	int GetNumU() { return numU; }
	int GetNumV() { return numV; }
	void SetNumU(int _numU) { numU = _numU; }
	void SetNumV(int _numV) { numV = _numV; }
	
	// 色関係
	DirectX::SimpleMath::Color GetColor(void) 
	{ return color; }
	void SetColor(float _r, float _g, float _b, float _a) {
		color.x = _r,
		color.y = _g,
		color.z = _b,
		color.w = _a;
	}

	std::vector<std::string> GetData() const;
	bool SetData(std::vector<std::string> _data);
};