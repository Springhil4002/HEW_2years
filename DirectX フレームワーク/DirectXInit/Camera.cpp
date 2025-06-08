#include "Renderer.h"
#include "Camera.h"
#include "Application.h"

using namespace DirectX::SimpleMath;

//===============================================
//����������
//===============================================
void Camera::Init()
{
	m_Position = Vector3(0.0f, 0.0f, 0.0f);
	m_Target = Vector3(0.0f, 0.0f, 0.0f);
}

//===============================================
//�X�V����
//===============================================
void Camera::Update()
{

}

//===============================================
//�`�揈��
//===============================================
void Camera::Draw()
{
	// �r���[�ϊ����쐬
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 front = Vector3(0.0f, 0.0f, -1.0f);
	m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position+front, m_Target, up); 
	Renderer::SetViewMatrix(&m_ViewMatrix);

	//�v���W�F�N�V�����s��̐���
	constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);    // ����p

	float aspectRatio = static_cast<float>(Application::GetWidth()) / static_cast<float>(Application::GetHeight());	// �A�X�y�N�g��	
	float nearPlane = 1.0f;       // �j�A�N���b�v
	float farPlane = 1000.0f;      // �t�@�[�N���b�v

	//�v���W�F�N�V�����s��̐���
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
//�������
//===============================================
void Camera::Uninit()
{

}

