#pragma once
#include<string>
#include<set>

// •„†‚ğ•t—^AíœAŒŸõ‚Å‚«‚é
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

