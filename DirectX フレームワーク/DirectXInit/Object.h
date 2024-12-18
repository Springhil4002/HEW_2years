#pragma once
#include <math.h>
#include <simpleMath.h>
#include"Tags.h"
#include"Scene.h"

class Object {
protected:
	// SRT���(�p�����)
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

public:	
	// ���C���[
	int layer;

	// �^�O
	Tags tags;
	
	Object() {}
	~Object() {}

	virtual void Init() {}		// ����������
	virtual void Update() {};	// �X�V����
	virtual void Draw() {};		// �`�揈��
	virtual void Uninit() {};	// �������

	// �e��Z�b�^�[
	void SetPos(float _x, float _y, float _z);				//���W���Z�b�g
	void SetRotation(float _x, float _y, float _z);			//�p�x���Z�b�g
	void SetScale(float _x, float _y, float _z);			//�傫�����Z�b�g

	DirectX::SimpleMath::Vector3 GetPos() const;

	// �I�u�W�F�N�g�̐���
	template<class T>
	static T* Create()
	{
		T* buf = new T;
		Scene::GetInstance()->GetObjects()->insert(buf);
		return buf;
	}

	// �I�u�W�F�N�g�̍폜
	static void Delete(Object* _object);

	// 2�̃I�u�W�F�N�g�̏Փ˔���
	static bool Collision(Object* _object1, Object* _object2);
};