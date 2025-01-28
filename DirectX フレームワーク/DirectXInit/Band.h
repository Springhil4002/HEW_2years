#pragma once
#include <set>
#include <math.h>
#include "Entity.h"
#include "BandTip.h"
#include "Delay.h"

class Band : public Entity
{
	friend class BandTip;
private: 
	enum Status
	{
		DEFAULT,
		STOP,
		LIMIT,
		REVERSE
	};

	// �o���h�̏��
	Status status;
	// �������Object�p�̃^�O
	std::string objectTag;
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
	
	Delay* delay;
	bool sendDelay;
public:
	int L;
	
	// �R���X�g���N�^�E�f�X�g���N�^�Ő�[�̊Ǘ�
	Band();
	~Band() {  }

	void Init();
	void Update();
	void Uninit();

	void Add(Object* _object);
	void Remove(Object* _object);

	// �Q�b�^�[�E�Z�b�^�[
	void SetLength(int _length);		// band�̈���������n���֐�
								
	float GetPullLevel()				// �ǂꂾ�����������Ă邩������Ă���֐�
	{return pullLevel; }

	void SetObject(std::string _tag);
	void ResetObject();

	std::vector<std::string> GetData() const;
	bool SetData(std::vector<std::string> _data);
};