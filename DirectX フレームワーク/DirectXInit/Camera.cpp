#include "Renderer.h"
#include "Camera.h"
#include "Application.h"

using namespace DirectX::SimpleMath;

//===============================================
//初期化処理
//===============================================
void Camera::Init()
{
	m_Position = Vector3(0.0f, 0.0f, 0.0f);
	m_Target = Vector3(0.0f, 0.0f, 0.0f);
}

//===============================================
//更新処理
//===============================================
void Camera::Update()
{

}

//===============================================
//描画処理
//===============================================
void Camera::Draw()
{
	// ビュー変換後列作成
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 front = Vector3(0.0f, 0.0f, -1.0f);
	m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position+front, m_Target, up); 
	Renderer::SetViewMatrix(&m_ViewMatrix);

	//プロジェクション行列の生成
	constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);    // 視野角

	float aspectRatio = static_cast<float>(Application::GetWidth()) / static_cast<float>(Application::GetHeight());	// アスペクト比	
	float nearPlane = 1.0f;       // ニアクリップ
	float farPlane = 1000.0f;      // ファークリップ

	//プロジェクション行列の生成
	Matrix projectionMatrix;

	int type = TYPE_2D;
	switch (type)
	{
	case TYPE_2D:
		projectionMatrix = DirectX::XMMatrixOrthographicLH(SCREEN_WIDTH,SCREEN_HEIGHT,nearPlane,farPlane);
		break;
	case TYPE_3D:
		projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);
		break;
	default:
		break;
	}
	

	Renderer::SetProjectionMatrix(&projectionMatrix);
}

//===============================================
//解放処理
//===============================================
void Camera::Uninit()
{

}

