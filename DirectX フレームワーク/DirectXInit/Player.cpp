#include "Player.h"

using namespace DirectX::SimpleMath;

//===================================================================
// �R���X�g���N�^
//===================================================================
Player::Player():velocity(0.0f),gravity(9.8f),jumpSpeed(50.0f),isJumping(false)
{

}

//===================================================================
// ����������
//===================================================================
void Player::Init(const std::string& _filename)
{
	// ���_�f�[�^
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

	// ���_�o�b�t�@����
	m_VertexBuffer.Create(vertices);

	// �C���f�b�N�X�o�b�t�@����
	std::vector<unsigned int> indices;
	indices.resize(4);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;

	// �C���f�b�N�X�o�b�t�@����
	m_IndexBuffer.Create(indices);

	// �V�F�[�_�I�u�W�F�N�g����
	m_Shader.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");

	// �e�N�X�`�����[�h
	bool sts = m_Texture.Load(_filename);
	assert(sts == true);
}

//===================================================================
// �X�V����
//===================================================================
void Player::Update(float _deltaTime)
{
	Walk();
	Jump();
	if (isJumping) {
		// deltaTime�̓t���[���Ԃ̎���
		velocity -= gravity * ;
		m_Position.y += velocity * deltaTime;

		// �n�ʂɒ��n�������ǂ����̃`�F�b�N
		// �����ɓ����蔻��̎���
		//if ()
		//{
		// m_Position.y = 0.0f;
		//	isJumping = false;
		//	velocity = 0.0f;
		//}
	}
}

//===================================================================
// �`�揈��
//===================================================================
void Player::Draw()
{
	// SRT���쐬
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
	Renderer::SetWorldMatrix(&worldmtx);	// GPU�ɃZ�b�g

	// �`��̏���
	ID3D11DeviceContext* deviceContext;
	deviceContext = Renderer::GetDeviceContext();

	// �g�|���W�[���Z�b�g(�v���~�e�B�u�^�C�v)
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	m_Shader.SetGPU();
	m_VertexBuffer.SetGPU();
	m_IndexBuffer.SetGPU();
	m_Texture.SetGPU();

	deviceContext->DrawIndexed(
		4,			// �`�悷��C���f�b�N�X�̐�(�l�p�`������4)
		0,			// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
		0);
}

//===================================================================
// �I������
//===================================================================
void Player::Uninit()
{
	delete this;
}

//===================================================================
// �v���C���[�̍��E�ړ�����
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
// �v���C���[�̃W�����v����
//===================================================================
void Player::Jump() {
	if (input.GetKeyPress(VK_SPACE) && isJumping == false)
	{
		isJumping = true;
		velocity = jumpSpeed;
	}
}

