#pragma once
#include "Entity.h"
#include "BandTip.h"
class Band : public Entity
{
private:
	// ��[�̃C���X�^���X
	BandTip* tip;

public:
	// �R���X�g���N�^�E�f�X�g���N�^�Ő�[�̊Ǘ�
	Band() { tip = Object::Create<BandTip>(); }
	~Band() { Object::Delete(tip); }

public:
	void Init();
	void Update();
};

