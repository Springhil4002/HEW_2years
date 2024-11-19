#pragma once
#include <stdio.h>
#include "input.h"
#include "Object.h"

class Scene
{
protected:
	Input input;		//���͌n�C���X�^���X
public:
	Scene();			//�R���X�g���N�^(�����������֐�)
	virtual ~Scene();	//�f�X�g���N�^	(��������֐�)

	//�������z�֐�
	virtual void Update() = 0;	//�X�V�����֐�
	virtual void Draw() = 0;	//�`�揈���֐�	

	// �I�u�W�F�N�g���Ǘ����郊�X�g
	std::vector<Object*>GameObjectList;
	// �I�u�W�F�N�g���擾����֐�
	Object* GetGameObject(const std::string& _name);
	void AddGameObject(std::string _name);
};