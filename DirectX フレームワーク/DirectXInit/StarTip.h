#pragma once
#include "Quad.h"

class StarTip
	: public Quad
{
public:

	static bool geting;	// starTip�̊l���t���O
	static bool seting;	// starTip�̃Z�b�g�t���O

	StarTip() {}		// �R���X�g���N�^
	~StarTip() {}		// �f�X�g���N�^

	// �I�[�o�[���C�h�����֐�
	void Init();		// ����������
	void Update();		// �X�V����
};