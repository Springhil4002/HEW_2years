#pragma once
#include <stdio.h>
#include "input.h"
#include "Object.h"
#include "Quad.h"
#include "Ground.h"
#include "Player.h"
#include "Physic.h"

#define BACKGROUND_X (1920)
#define BACKGROUND_Y (1080)
#define BLOCK_SIZE	(60.0f)

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