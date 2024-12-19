#include "Player.h"
#include "Ground.h"
#include "Band.h"
using namespace DirectX::SimpleMath;

#define GROUND_OFFSET_X (-930.0f)
#define GROUND_OFFSET_Y (-510.0f)

//===================================================================
// �R���X�g���N�^
//===================================================================
Player::Player() : velocity(1.5f), gravity(3.0f), jumpSpeed(50.0f), isJumping(true), isFalling(false), isGrabing(false), isMoving(false)
{

}

//===================================================================
// ����������
//===================================================================
void Player::Init()
{
	const float playerX = GROUND_OFFSET_X + (2.5f * BLOCK_SIZE);
	const float playerY = GROUND_OFFSET_Y + (2.5f * BLOCK_SIZE);
	SetTex("asset/Texture/player.png");// �v���C���[��������
	SetPos(playerX, playerY, 0.0f);	// ���W��ݒ�
	SetScale(BLOCK_SIZE, 2 * BLOCK_SIZE, 0.0f);	// �傫����ݒ�
	m_Acceleration.y = -gravity;
}

//===================================================================
// �X�V����
//===================================================================
void Player::Update()
{	
	State();	// ��ԊǗ�

	Walk();		// ��������
	Jump();		// ���􏈗�
	Resist();	// ��R����
	Entity::Update();	// �Փˏ���

	auto allQuad = Scene::GetInstance()->GetObjects<Quad>();
	for (auto& x : allQuad)
	{
		if (x->tags.SearchTag("check"))
		{
			if ((Scene::input.GetButtonRelease(XINPUT_RIGHT_SHOULDER) ||
				Scene::input.GetButtonRelease(XINPUT_LEFT_SHOULDER)))
			{
				x->SetPos(200, 0, 0);
			}
			else
			{
				x->SetPos(0, 0, 0);
			}

			break;
		}
	}

}

//===================================================================
// �`�揈��
//===================================================================
//void Player::Draw()
//{
//	// SRT���쐬
//	Matrix r = Matrix::CreateFromYawPitchRoll(
//		m_Rotation.y,
//		m_Rotation.x,
//		m_Rotation.z);
//
//	Matrix t = Matrix::CreateTranslation(
//		m_Position.x,
//		m_Position.y,
//		m_Position.z);
//
//	Matrix s = Matrix::CreateScale(
//		m_Scale.x,
//		m_Scale.y,
//		m_Scale.z);
//
//	Matrix worldmtx;
//	worldmtx = s * r * t;
//	Renderer::SetWorldMatrix(&worldmtx);	// GPU�ɃZ�b�g
//
//	// �`��̏���
//	ID3D11DeviceContext* deviceContext;
//	deviceContext = Renderer::GetDeviceContext();
//
//	// �g�|���W�[���Z�b�g(�v���~�e�B�u�^�C�v)
//	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//
//	m_Shader.SetGPU();
//	m_VertexBuffer.SetGPU();
//	m_IndexBuffer.SetGPU();
//	m_Texture.SetGPU();
//
//	deviceContext->DrawIndexed(
//		4,			// �`�悷��C���f�b�N�X�̐�(�l�p�`������4)
//		0,			// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
//		0);
//}

//===================================================================
// �I������
//===================================================================
//void Player::Uninit()
//{
//	
//}

//===================================================================
// �v���C���[�̏�ԑJ�ڏ���
//===================================================================
void Player::State() {
	if (m_Velocity.y < -0.001f)
	{
		state = FALLING;
	}

	if (m_Velocity.y > 0.001f)
	{
		state = FLYING;
	}

	if (state == FALLING && -0.001f < m_Velocity.y && m_Velocity.y < 0.001f)
	{
		state = ONGROUND;
	}

	if (Scene::input.GetKeyPress(VK_E) ||
	   (Scene::input.GetButtonPress(XINPUT_RIGHT_SHOULDER) && 
		Scene::input.GetButtonPress(XINPUT_LEFT_SHOULDER) ) )
	{
		auto allBand = Scene::GetInstance()->GetObjects<BandTip>();
		for (auto& band : allBand)
		{
			if (Object::Collision(this, band))
			{
				if (moveDirection == band->MoveDirection())
				{
					grabState = GRAB;
					if (m_Velocity.x > -0.01f && moveDirection == LEFT || m_Velocity.x < 0.01f && moveDirection == RIGHT)
					{
						band->isGrabing = true;
						band->SetVelo(m_Velocity.x, 0, 0);
						// ������:���ԁA������:����
						Scene::input.SetVibration(30, 10 * band->GetPullLeveL());	
					}
				}
			}
			else
			{
				band->isGrabing = false;
				band->SetPullLeveL(0);
			}
		}
	}
	else
	{
		grabState = DEFAULT;
	}

	if (Scene::input.GetKeyRelease(VK_E) || 
	   (Scene::input.GetButtonRelease(XINPUT_RIGHT_SHOULDER) ||
		Scene::input.GetButtonRelease(XINPUT_LEFT_SHOULDER) ) )
	{
		auto allBand = Scene::GetInstance()->GetObjects<BandTip>();
		for (auto& band : allBand)
		{
			band->isGrabing = false;
		}
	}

	if (m_Velocity.LengthSquared() > 0.000001f)
	{
		groundState = MOVE;
	}
	else
	{
		groundState = STOP;
	}
}

//===================================================================
// �v���C���[�̍��E�ړ�����
//===================================================================
void Player::Walk() {
	if (Scene::input.GetKeyPress(VK_D) || 
	   (Scene::input.GetLeftAnalogStick().x >= 0.7f))
	{
		if (grabState == DEFAULT)
		{
			moveDirection = RIGHT;
			if (state == ONGROUND)
				m_Velocity.x += velocity;
			else
				m_Velocity.x += velocity / 1.5f;
		}
		else
		{
			if (moveDirection == LEFT)
			{
				m_Velocity.x += velocity / 3.0f;
			}
		}
	}

	if (Scene::input.GetKeyPress(VK_A) ||
	   (Scene::input.GetLeftAnalogStick().x <= -0.7f))
	{
		if (grabState == DEFAULT)
		{
			moveDirection = LEFT;
			if (state == ONGROUND)
				m_Velocity.x -= velocity;
			else
				m_Velocity.x -= velocity / 1.5f;
		}
		else
		{
			if (moveDirection == RIGHT)
			{
				m_Velocity.x -= velocity / 3.0f;
			}
		}
	}
}

//===================================================================
// �v���C���[�̃W�����v����
//===================================================================
void Player::Jump() {
	if (state == ONGROUND && grabState == DEFAULT)	
	{
		if (Scene::input.GetKeyTrigger(VK_SPACE) ||
			Scene::input.GetButtonTrigger(XINPUT_A))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE001);
			m_Velocity.y += jumpSpeed;
		}
	}
}

//===================================================================
// �v���C���[�̒�R����
//===================================================================
void Player::Resist() {
	m_Velocity /= 1.2f;
}