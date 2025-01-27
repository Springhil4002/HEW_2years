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
	// 頂点データ
	std::vector<VERTEX_3D>	vertices;

	vertices.resize(4);
	
	vertices[0].position = Vector3(-0.5f,  0.5f, 0);
	vertices[1].position = Vector3( 0.5f,  0.5f, 0);
	vertices[2].position = Vector3(-0.5f, -0.5f, 0);
	vertices[3].position = Vector3( 0.5f, -0.5f, 0);

	vertices[0].color = Color(GetColor());
	vertices[1].color = Color(GetColor());
	vertices[2].color = Color(GetColor());
	vertices[3].color = Color(GetColor());

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

void Quad::SetTex(const std::string& _filename, int _splitX, int _splitY, int _numU, int _numV, float _r, float _g, float _b, float _a)
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

	vertices[0].color = Color(_r, _g, _b, _a);
	vertices[1].color = Color(_r, _g, _b, _a);
	vertices[2].color = Color(_r, _g, _b, _a);
	vertices[3].color = Color(_r, _g, _b, _a);

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

std::vector<std::string> Quad::GetData() const
{
	std::vector<std::string> buf;

	// オブジェクト名
	buf.push_back("Quad");

	// オブジェクトの基本情報
	auto objData = Object::GetData();
	buf.insert(buf.end(), objData.begin(), objData.end());

	// サイズの情報
	buf.push_back(std::to_string(m_Scale.x));
	buf.push_back(std::to_string(m_Scale.y));

	// テクスチャの情報
	buf.push_back(m_Texture.FileName());

	return buf;
}

bool Quad::SetData(std::vector<std::string> _data)
{
	if (_data.front() == "Quad")
	{
		std::vector<std::string> objBuf(6 + stoi(_data[6]));
		std::copy(_data.begin() + 1, _data.begin() + 7 + stoi(_data[6]), objBuf.begin());
		Object::SetData(objBuf);

		m_Scale.x = stoi(_data[7 + stoi(_data[6])]);
		m_Scale.y = stoi(_data[8 + stoi(_data[6])]);

		SetTex(_data[9 + stoi(_data[6])]);

		return true;
	}
	else
	{
		return false;
	}
}