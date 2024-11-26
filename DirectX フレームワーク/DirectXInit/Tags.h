#pragma once
#include<string>
#include<set>

// 符号を付与、削除、検索できる
class Tags
{
private:
	std::set<std::string> tags;

public:	
	Tags() {}	// コンストラクタ
	~Tags() {}	// デストラクタ

	void AddTag(const std::string _tag);			// タグの追加
	void RemoveTag(const std::string _tag);			// タグの部分削除
	bool SearchTag(const std::string _tag) const;	// タグを探す
	void ClearTags();								// タグの全削除
};

