#pragma once
#include<string>
#include<set>
#include<vector>
// 符号を付与、削除、検索できる
class Tags
{
private:
	std::set<std::string> tags;

public:	
	Tags() {}	// コンストラクタ
	~Tags() {}	// デストラクタ

	std::set<std::string>::const_iterator begin() const;
	std::set<std::string>::const_iterator end() const;

	void AddTag(const std::string _tag);			// タグの追加
	void RemoveTag(const std::string _tag);			// タグの部分削除
	bool SearchTag(const std::string _tag) const;	// タグを探す
	void ClearTags();								// タグの全削除
	std::vector<std::string> GetData() const;
};

