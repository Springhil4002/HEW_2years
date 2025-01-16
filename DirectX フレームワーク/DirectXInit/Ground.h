#pragma once

#include "Entity.h"
#include "TextureManager.h"

//=======================================================================================
// Groundクラス
//=======================================================================================
class Ground :public Entity {
public:
	// オーバーライドした関数
	void Init();	// 初期化処理
	//void Update();	// 更新処理
	//void Draw();	// 描画処理
	//void Uninit();	// 解放処理

	std::vector<std::string> GetData() const;
	bool SetData(std::vector<std::string> _data);
};