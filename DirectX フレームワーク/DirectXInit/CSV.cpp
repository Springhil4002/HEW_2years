#include "CSV.h"
#include <fstream>
#include <sstream>

std::vector<std::vector<std::string>>::const_iterator CSV::begin() const
{
    return data.begin();
}

std::vector<std::vector<std::string>>::const_iterator CSV::end() const
{
    return data.end();
}

void CSV::push_back(std::vector<std::string> _strs)
{
    data.push_back(_strs);
}

void CSV::Load(std::string _fileName)
{
    std::string str_buf;
    std::string str_conma_buf;
    std::vector<std::string> row_buf;

    // 読み込むcsvファイルを開く
    std::ifstream ifs_csv_file(_fileName);

    // 初期化
    data.clear();
    // getline関数で1行ずつ読み込む
    while (getline(ifs_csv_file, str_buf))
    {
        row_buf.clear();
        // 「,」区切りごとにデータを読み込むためにistringstream型にする
        std::istringstream i_stream(str_buf);
        // 「,」区切りごとにデータを読み込む
        while (getline(i_stream, str_conma_buf, ','))
        {
            // 読み込んだデータを格納
            row_buf.push_back(str_conma_buf);
        }
        data.push_back(row_buf);
    }
}

// csvファイルに書き込む
void CSV::Save(std::string _fileName)
{
    // 書き込むcsvファイルを開く(std::ofstreamのコンストラクタで開く)
    std::ofstream ofs_csv_file(_fileName);

    for (auto& row : data)
    {
        for (auto& str : row)
        {
            // csvファイルに書き込む
            ofs_csv_file << str << ',';
        }
        // 改行する
        ofs_csv_file << std::endl;
    }
}