#pragma once
#include <set>
#include <math.h>
#include "Entity.h"
#include "BandTip.h"
class Band : public Entity
{
private:
	// ��[�̃C���X�^���X
	BandTip* tip;
	// �M�U�M�U�����̃C���X�^���X
	std::set<Quad*> jagged;
	// �������Object�B
	std::set<Object*> objects;
	// �ǂ񂾂����������Ă邩�x
	float pullLevel;
	// �O�̍��W
	DirectX::SimpleMath::Vector3 oldPos;
public:
	// �R���X�g���N�^�E�f�X�g���N�^�Ő�[�̊Ǘ�
	Band() { tip = Object::Create<BandTip>(); }
	~Band() { Object::Delete(tip); }

public:
	void Init();
	void Update();
	void Uninit();

	void Add(Object* _object);
	void Remove(Object* _object);
};