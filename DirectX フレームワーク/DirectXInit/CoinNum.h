#pragma once
#include "Quad.h"

class CoinNum
	: public Quad
{
public:
	CoinNum() {}			// �R���X�g���N�^
	~CoinNum() {}			// �f�X�g���N�^

	// �I�[�o�[���C�h�����֐�
	void Init();		// ����������
	void Update();		// �X�V����
};