#pragma once
#include <math.h>
#include <simpleMath.h>
#include "Shader.h"
#include"Tags.h"

class Object {
private:
	static std::vector<Object*>* objInstance;

protected:
	// SRT���(�p�����)
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

	// �`��ׂ̈̏��i�����ڂɊւ�镔���j
	static Shader m_Shader; // �V�F�[�_�[

	// �^�O
	Tags tags;


public:	
	Object() { objInstance = new std::vector<Object*>; }
	~Object() { delete objInstance; }

	// �������z�֐�
	virtual void Init() {}	// ����������
	virtual void Update() = 0;	// �X�V����
	virtual void Draw() = 0;	// �`�揈��
	virtual void Uninit() = 0;	// �������

	// �e��Z�b�^�[
	void SetPos(float _x, float _y, float _z);				//���W���Z�b�g
	void SetRotation(float _x, float _y, float _z);			//�p�x���Z�b�g
	void SetScale(float _x, float _y, float _z);			//�傫�����Z�b�g

	// �^�O����
	bool SearchTag(const std::string _tag) const;

	static void CreateShader();
	static std::vector<Object*>* GetInstance();

	// ���̌^�̃I�u�W�F�N�g��Ԃ���
	template<class T>
	static std::vector<T*> GetObj()
	{
		// �Ԃ����
		std::vector<T*> ret;

		// �S�I�u�W�F�N�g����T����
		for (auto& all : *Object::GetInstance())
		{
			// �_�C�i�~�b�N�L���X�g���Ă���Ȃ�ret�ɂ����
			T* obj = dynamic_cast<T*>(all);
			if (obj != nullptr)
			{
				ret.push_back(obj);
			}
		}
		return ret;
	}

	// 2�̃I�u�W�F�N�g�̏Փ˔���
	static bool Collision(Object* _object1, Object* _object2);
};