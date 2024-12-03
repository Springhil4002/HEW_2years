#include "TextureManager.h"
#include<iostream>

// static�Ȃ��
std::map<std::string, Texture> TextureManager::textures;
std::set<std::string> TextureManager::loaded;
std::string TextureManager::last;

bool TextureManager::Load(std::string _filename)
{
	filename = _filename;
	if (loaded.count(filename))
	{
		// �����ǂݍ���ł���Ȃ琬����Ԃ��ĉ������Ȃ�
		return true;
	}
	else
	{
		std::cout << filename << std::endl; // �f�o�b�O�p
		// ���߂ĂȂ�loaded�ɂԂ�����
		loaded.insert(filename);
		return textures[filename].Load(filename);
	}
}

void TextureManager::SetGPU()
{
	if (last != filename)
	{
		textures[filename].SetGPU();
		last = filename;
	}
}

void TextureManager::Clear()
{
	last = "";
	loaded.clear();
	textures.clear();
}