#pragma once
#include <stdio.h>
#include "input.h"
#include "Object.h"
#include "Quad.h"
#include "Ground.h"

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
};