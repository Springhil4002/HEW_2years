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

    // �t�@�C����ǂݍ���(.csv)
    void Load(std::string _fileName);

    // �t�@�C���ɕۑ�����(.csv)
    void Save(std::string _fileName);
};

