#pragma once
#include<map>
#include<set>
#include"Texture.h"

class TextureManager
{
private:
	// 
	static std::map<std::string, Texture> textures;
	static std::set<std::string> loaded;
	static std::string last;
	std::string filename;

public:
	TextureManager() {}
	~TextureManager() {}

	bool Load(std::string _filename);
	void SetGPU();
	static void Clear();
};

