#include "Tags.h"

// タグの付与
void Tags::AddTag(const std::string _tag)
{
	tags.insert(_tag);
}

// タグの部分削除
void Tags::RemoveTag(const std::string _tag)
{
	tags.erase(_tag);
}

// タグの検索
bool Tags::SearchTag(const std::string _tag) const
{
	return tags.count(_tag);
}

// タグの全削除
void Tags::ClearTags()
{
	tags.clear();
}

std::vector<std::string> Tags::GetData() const
{
	std::vector<std::string> buf;
	buf.push_back("Tags");
	buf.push_back(std::to_string(tags.size()));
	for (auto& tag : tags)
	{
		buf.push_back(tag);
	}
	return buf;
}