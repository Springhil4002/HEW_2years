#pragma once
#include <set>
#include <math.h>
#include "Entity.h"
#include "BandTip.h"
class UpBand : public Entity
{
private:
	// �������Object�p�̃^�O
	std::string objectTag;
	// ��������镔���̃I�u�W�F�N�g
	std::set<Quad*> jagged;
	// �������Object�B
	std::set<Object*> objects;
	// �ǂ񂾂����������Ă邩�x
	float pullLevel;
public:
	int L;

	// �R���X�g���N�^�E�f�X�g���N�^�Ő�[�̊Ǘ�
	UpBand() : L(4) {}
	~UpBand() { }

	void Init();
	void Update();
	void Uninit();

	void Add(Object* _object);
	void Remove(Object* _object);

	// �Q�b�^�[�E�Z�b�^�[
	void SetLength(int _length);		// band�̈���������n���֐�

	float GetPullLevel()				// �ǂꂾ�����������Ă邩������Ă���֐�
	{
		return pullLevel;
	}

	void SetObject(std::string _tag);

	std::vector<std::string> GetData() const;
	bool SetData(std::vector<std::string> _data);
};