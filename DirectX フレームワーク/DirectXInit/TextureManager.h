#pragma once
#include<map>
#include<set>
#include"Texture.h"

class TextureManager
{
private:
	// �ǂݍ��񂾃e�N�X�`��������Ƃ�
	static std::map<std::string, Texture> textures;
	
	// �ǂݍ��񂾃e�N�X�`���̖��O������Ƃ�
	static std::set<std::string> loaded;

	// �Ō�ɓǂݍ��񂾂�̖��O������Ƃ�
	static std::string last;

	// �ǂݍ��ޖ��O�����Ƃ�
	std::string filename;

public:
	TextureManager() {}
	~TextureManager() {}

	// �ǂݍ���
	bool Load(std::string _filename);
	
	// GPU�ɃZ�b�g����炵��
	void SetGPU();

	// �ǂݍ��񂾃e�N�X�`���̑S�폜
	static void Clear();

	std::string FileName() const { return filename; }
};

