#pragma once
#include "Input.h"
#include "Entity.h"

class Player 
	: public Entity {
private:
	//Input input;			// ���̓C���X�^���X
	float velocity; 		// ���x
	const float gravity;	// �d��
	const float jumpSpeed;	// �W�����v�̏����x
	bool isFalling;
	bool isJumping;			// �W�����v���Ă邩�̔ۂ��̃t���O
public:
	Player();		// �R���X�g���N�^

	// �I�[�o�[���C�h�����֐�
	void Init();	// ����������
	void Update();	// �X�V����
	//void Draw();	// �`�揈��
	//void Uninit();	// �������

	// �v���C���[�̋���
	void Walk();		// ���E�ړ�(����)
	void Jump();		// �W�����v
	void GrabBand();	// �����o���h��G��(�͂�)
	void PullBand();	// �����o���h����������
};