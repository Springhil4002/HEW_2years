#include "Quad.h"

using namespace DirectX::SimpleMath;

Shader Quad::m_Shader; // シェーダー

//===================================================================
// 初期化処理
//===================================================================
void Quad::Init()
{
	
}
//===================================================================
// 更新処理
//===================================================================
void Quad::Update()
{
	/*if (old != moveDirection)
	{*/
		// 頂点データ
		std::vector<VERTEX_3D>	vertices;

		vertices.resize(4);

		vertices[0].position = Vector3(-0.5f,  0.5f, 0);
		vertices[1].position = Vector3( 0.5f,  0.5f, 0);
		vertices[2].position = Vector3(-0.5f, -0.5f, 0);
		vertices[3].position = Vector3( 0.5f, -0.5f, 0);

		vertices[0].color = Color(1, 1, 1, 1);
		vertices[1].color = Color(1, 1, 1, 1);
		vertices[2].color = Color(1, 1, 1, 1);
		vertices[3].color = Color(1, 1, 1, 1);

		if (moveDirection == RIGHT)
		{
			vertices[0].uv = Vector2(1.0f/GetSplitX()* GetNumU(),	 1.0f/GetSplitY()* GetNumV());
			vertices[1].uv = Vector2(1.0f/GetSplitX()*(GetNumU()+1), 1.0f/GetSplitY()* GetNumV());
			vertices[2].uv = Vector2(1.0f/GetSplitX()* GetNumU(),	 1.0f/GetSplitY()*(GetNumV()+1));
			vertices[3].uv = Vector2(1.0f/GetSplitX()*(GetNumU()+1), 1.0f/GetSplitY()*(GetNumV()+1));
		}
		else
		{
			vertices[0].uv = Vector2(1.0f/GetSplitX()*(GetNumU()+1), 1.0f/GetSplitY()* GetNumV());
			vertices[1].uv = Vector2(1.0f/GetSplitX()* GetNumU(),	 1.0f/GetSplitY()* GetNumV());
			vertices[2].uv = Vector2(1.0f/GetSplitX()*(GetNumU()+1), 1.0f/GetSplitY()*(GetNumV()+1));
			vertices[3].uv = Vector2(1.0f/GetSplitX()* GetNumU(),	 1.0f/GetSplitY()*(GetNumV()+1));
		}

		// 頂点バッファ生成
		m_VertexBuffer.Create(vertices);

	//	// 更新
	//	old = moveDirection;
	//}
}

//===================================================================
// 描画処理
//===================================================================
void Quad::Draw()
{
	// SRT情報作成
	Matrix r = Matrix::CreateFromYawPitchRoll(
		m_Rotation.y,
		m_Rotation.x,
		m_Rotation.z);

	Matrix t = Matrix::CreateTranslation(
		m_Position.x,
		m_Position.y,
		m_Position.z);

	Matrix s = Matrix::CreateScale(
		m_Scale.x,
		m_Scale.y,
		m_Scale.z);

	Matrix worldmtx;
	worldmtx = s * r * t;
	Renderer::SetWorldMatrix(&worldmtx);	// GPUにセット

	// 描画の処理
	ID3D11DeviceContext* deviceContext;
	deviceContext = Renderer::GetDeviceContext();

	// トポロジーをセット(プリミティブタイプ)
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	m_Shader.SetGPU();
	m_VertexBuffer.SetGPU();
	m_IndexBuffer.SetGPU();
	m_Texture.SetGPU();

	deviceContext->DrawIndexed(
		4,			// 描画するインデックスの数(四角形だから4)
		0,			// 最初のインデックスバッファの位置
		0);
}

//===================================================================
// 終了処理
//===================================================================
void Quad::Uninit()
{
	
}

void Quad::SetTex(const std::string& _filename, int _splitX, int _splitY, int _numU, int _numV)
{
	SetSplitX(_splitX);
	SetSplitY(_splitY);
	SetNumU(_numU);
	SetNumV(_numV);

	// 頂点データ
	std::vector<VERTEX_3D>	vertices;

	vertices.resize(4);

	vertices[0].position = Vector3(-0.5f, 0.5f, 0);
	vertices[1].position = Vector3(0.5f, 0.5f, 0);
	vertices[2].position = Vector3(-0.5f, -0.5f, 0);
	vertices[3].position = Vector3(0.5f, -0.5f, 0);

	vertices[0].color = Color(1, 1, 1, 1);
	vertices[1].color = Color(1, 1, 1, 1);
	vertices[2].color = Color(1, 1, 1, 1);
	vertices[3].color = Color(1, 1, 1, 1);

	if (moveDirection == RIGHT)
	{
		vertices[0].uv = Vector2(1.0f/_splitX* _numU,	  1.0f/_splitY*  _numV);
		vertices[1].uv = Vector2(1.0f/_splitX*(_numU+1),  1.0f/_splitY*  _numV);
		vertices[2].uv = Vector2(1.0f/_splitX* _numU,	  1.0f/_splitY* (_numV+1));
		vertices[3].uv = Vector2(1.0f/_splitX*(_numU+1),  1.0f/_splitY* (_numV+1));
	}
	else
	{
		vertices[0].uv = Vector2(1.0f/_splitX*(_numU+1), 1.0f/_splitY* _numV);
		vertices[1].uv = Vector2(1.0f/_splitX* _numU,	 1.0f/_splitY* _numV);
		vertices[2].uv = Vector2(1.0f/_splitX*(_numU+1), 1.0f/_splitY*(_numV+1));
		vertices[3].uv = Vector2(1.0f/_splitX* _numU,	 1.0f/_splitY*(_numV+1));
	}

	// 頂点バッファ生成
	m_VertexBuffer.Create(vertices);
	
	// インデックスバッファ生成
	std::vector<unsigned int> indices;
	indices.resize(4);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;

	// インデックスバッファ生成
	m_IndexBuffer.Create(indices);
	
	// テクスチャロード
	bool sts = m_Texture.Load(_filename);
	assert(sts == true);
}