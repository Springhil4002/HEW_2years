#pragma once
#include "Input.h"
#include "Entity.h"
#include "SceneManager.h"

class Player : public Entity {
private:
	enum STATE
	{
		FLYING,
		ONGROUND,
		FALLING
	};

	enum MOVESTATE
	{
		STOP,
		MOVE
	};

	enum GRABSTATE
	{
		DEFAULT,
		GRAB
	};

	float velocity; 		// ���x
	const float gravity;	// �d��
	const float jumpSpeed;	// �W�����v�̏����x
	bool isFalling;			// �����Ă邩�̃t���O
	bool isJumping;			// �W�����v���Ă邩�̔ۂ��̃t���O
	bool isGrabing;			// ���������Ă邩�̃t���O
	bool isMoving;

	STATE state;
	MOVESTATE groundState;
	GRABSTATE grabState;

	public:
	Player();		// �R���X�g���N�^

	// �I�[�o�[���C�h�����֐�
	void Init();	// ����������
	void Update();	// �X�V����

	// �v���C���[�̋���
	void State();		// ��ԑJ��
	void Walk();		// ���E�ړ�(����)
	void Jump();		// �W�����v
	void Resist();		// ��R
	void GrabBand();	// �����o���h��G��(�͂�)
	void PullBand();	// �����o���h����������
};