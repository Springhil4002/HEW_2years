#pragma once
#include<map>
#include<set>
#include"Texture.h"

class TextureManager
{
private:
	// 読み込んだテクスチャを入れるとこ
	static std::map<std::string, Texture> textures;
	
	// 読み込んだテクスチャの名前を入れるとこ
	static std::set<std::string> loaded;

	// 最後に読み込んだやつの名前を入れるとこ
	static std::string last;

	// 読み込む名前入れるとこ
	std::string filename;

public:
	TextureManager() {}
	~TextureManager() {}

	// 読み込み
	bool Load(std::string _filename);
	
	// GPUにセットするらしい
	void SetGPU();

	// 読み込んだテクスチャの全削除
	static void Clear();

	std::string FileName() const { return filename; }
};

