#pragma once

#include "Object.h"
#include "Com_Transform.h"
#include "Com_Quad.h"

class Object;

class Component
{
public:
	Component(){}				// �R���X�g���N�^
	virtual ~Component() {}		// �f�X�g���N�^

	// �R���|�[�l���g��������e�I�u�W�F�N�g���w���|�C���^
	Object* Parent;				

	// �������z�֐�
	virtual void Start(){}		// ����������		
	virtual void Update(){}		// �X�V����
	virtual void Draw(){}		// �`�揈��
};