#pragma once
#include<string>
#include<set>
#include<vector>
// ������t�^�A�폜�A�����ł���
class Tags
{
private:
	std::set<std::string> tags;

public:	
	Tags() {}	// �R���X�g���N�^
	~Tags() {}	// �f�X�g���N�^

	std::set<std::string>::const_iterator begin() const;
	std::set<std::string>::const_iterator end() const;

	void AddTag(const std::string _tag);			// �^�O�̒ǉ�
	void RemoveTag(const std::string _tag);			// �^�O�̕����폜
	bool SearchTag(const std::string _tag) const;	// �^�O��T��
	void ClearTags();								// �^�O�̑S�폜
	std::vector<std::string> GetData() const;
};

