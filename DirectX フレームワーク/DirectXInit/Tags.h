#pragma once
#include<string>
#include<set>

// ������t�^�A�폜�A�����ł���
class Tags
{
private:
	std::set<std::string> tags;

public:
	Tags() {}
	~Tags() {}

	void AddTag(const std::string _tag);
	void RemoveTag(const std::string _tag);
	bool SearchTag(const std::string _tag) const;
	void ClearTags();
};

