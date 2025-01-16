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

    // �ǂݍ���csv�t�@�C�����J��
    std::ifstream ifs_csv_file(_fileName);

    // ������
    data.clear();
    // getline�֐���1�s���ǂݍ���
    while (getline(ifs_csv_file, str_buf))
    {
        row_buf.clear();
        // �u,�v��؂育�ƂɃf�[�^��ǂݍ��ނ��߂�istringstream�^�ɂ���
        std::istringstream i_stream(str_buf);
        // �u,�v��؂育�ƂɃf�[�^��ǂݍ���
        while (getline(i_stream, str_conma_buf, ','))
        {
            // �ǂݍ��񂾃f�[�^���i�[
            row_buf.push_back(str_conma_buf);
        }
        data.push_back(row_buf);
    }
}

// csv�t�@�C���ɏ�������
void CSV::Save(std::string _fileName)
{
    // ��������csv�t�@�C�����J��(std::ofstream�̃R���X�g���N�^�ŊJ��)
    std::ofstream ofs_csv_file(_fileName);

    for (auto& row : data)
    {
        for (auto& str : row)
        {
            // csv�t�@�C���ɏ�������
            ofs_csv_file << str << ',';
        }
        // ���s����
        ofs_csv_file << std::endl;
    }
}