#include "TextureManager.h"
#include<iostream>

// staticなやつら
std::map<std::string, Texture> TextureManager::textures;
std::set<std::string> TextureManager::loaded;
std::string TextureManager::last;

bool TextureManager::Load(std::string _filename)
{
	filename = _filename;
	if (loaded.count(filename))
	{
		// もう読み込んでいるなら成功を返して何もしない
		return true;
	}
	else
	{
		std::cout << filename << std::endl; // デバッグ用
		// 初めてならloadedにぶち込む
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