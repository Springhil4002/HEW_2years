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
	int L;
	
	// �R���X�g���N�^�E�f�X�g���N�^�Ő�[�̊Ǘ�
	Band(): L(4) { tip = Object::Create<BandTip>(); }
	~Band() { Object::Delete(tip); }

	void Init();
	void Update();
	void Uninit();

	void Add(Object* _object);
	void Remove(Object* _object);

	std::vector<std::string> GetData() const;
	bool SetData(std::vector<std::string> _data);
};