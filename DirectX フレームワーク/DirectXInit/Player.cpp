#include "Player.h"

using namespace DirectX::SimpleMath;

//===================================================================
// コンストラクタ
//===================================================================
Player::Player():velocity(0.0f),gravity(9.8f),jumpSpeed(50.0f),isJumping(false)
{

}

//===================================================================
// 初期化処理
//===================================================================
void Player::Init(const std::string& _filename)
{
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

	vertices[0].uv = Vector2(0, 0);
	vertices[1].uv = Vector2(1, 0);
	vertices[2].uv = Vector2(0, 1);
	vertices[3].uv = Vector2(1, 1);

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

	// シェーダオブジェクト生成
	m_Shader.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");

	// テクスチャロード
	bool sts = m_Texture.Load(_filename);
	assert(sts == true);
}

//===================================================================
// 更新処理
//===================================================================
void Player::Update(float _deltaTime)
{
	Walk();
	Jump();
	if (isJumping) {
		// deltaTimeはフレーム間の時間
		velocity -= gravity * ;
		m_Position.y += velocity * deltaTime;

		// 地面に着地したかどうかのチェック
		// ここに当たり判定の実装
		//if ()
		//{
		// m_Position.y = 0.0f;
		//	isJumping = false;
		//	velocity = 0.0f;
		//}
	}
}

//===================================================================
// 描画処理
//===================================================================
void Player::Draw()
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
void Player::Uninit()
{
	delete this;
}

//===================================================================
// プレイヤーの左右移動処理
//===================================================================
void Player::Walk() {
	if (input.GetKeyPress(VK_D))
	{
		m_Position.x += 0.5f;
	}
	if (input.GetKeyPress(VK_A))
	{
		m_Position.x -= 0.5f;
	}
}

//===================================================================
// プレイヤーのジャンプ処理
//===================================================================
void Player::Jump() {
	if (input.GetKeyPress(VK_SPACE) && isJumping == false)
	{
		isJumping = true;
		velocity = jumpSpeed;
	}
}

