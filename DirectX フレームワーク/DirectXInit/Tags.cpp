#include "Tags.h"

// �^�O�̕t�^
void Tags::AddTag(const std::string _tag)
{
	tags.insert(_tag);
}

// �^�O�̕����폜
void Tags::RemoveTag(const std::string _tag)
{
	tags.erase(_tag);
}

// �^�O�̌���
bool Tags::SearchTag(const std::string _tag) const
{
	return tags.count(_tag);
}

// �^�O�̑S�폜
void Tags::ClearTags()
{
	tags.clear();
}