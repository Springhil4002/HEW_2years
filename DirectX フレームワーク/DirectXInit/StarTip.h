#pragma once
#include "Quad.h"

class StarTip
	: public Quad
{
private:
	bool geting = false;	// starTip�̊l���t���O
	bool seting = false;	// starTip�̃e�N�X�`���Z�b�g�t���O
public:
	StarTip() {}		// �R���X�g���N�^
	~StarTip() {}		// �f�X�g���N�^

	// �I�[�o�[���C�h�����֐�
	void Init();		// ����������
	void Update();		// �X�V����

	// �Q�b�^�[�E�Z�b�^�[�֌W
	// starTip�̊l���t���O�̃Q�b�^�[�E�Z�b�^�[
	bool GetGeting() { return geting; }
	void SetGeting(bool _geting) {geting = _geting; }

	// starTip�̃e�N�X�`���Z�b�g�t���O�̃Q�b�^�[�E�Z�b�^�[�֌W
	bool GetSeting() { return seting; }
	void SetSeting(bool _seting) { seting = _seting; }
};