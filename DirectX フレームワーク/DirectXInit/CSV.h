#pragma once
#include <vector>
#include <string>

class CSV
{
private:
    std::vector<std::vector<std::string>> data;

public:
    CSV() {}
    ~CSV() {}

    std::vector<std::vector<std::string>>::const_iterator begin() const;
    std::vector<std::vector<std::string>>::const_iterator end() const;
    void push_back(std::vector<std::string> _strs);
    void clear();

    // ファイルを読み込む(.csv)
    void Load(std::string _fileName);

    // ファイルに保存する(.csv)
    void Save(std::string _fileName);
};

