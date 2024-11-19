#pragma once
#include <simpleMath.h>
#include "Shader.h"

class Object {

protected:
	// SRT���(�p�����)
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

	// �`��ׂ̈̏��i�����ڂɊւ�镔���j
	Shader m_Shader; // �V�F�[�_�[

public:
	// �������z�֐�
	virtual void Init() {}	// ����������
	virtual void Update() = 0;	// �X�V����
	virtual void Draw() = 0;	// �`�揈��
	virtual void Uninit() = 0;	// �������

	// �e��Z�b�^�[
	void SetPos(float _x, float _y, float _z);				//���W���Z�b�g
	void SetRotation(float _x, float _y, float _z);			//�p�x���Z�b�g
	void SetScale(float _x, float _y, float _z);			//�傫�����Z�b�g
};