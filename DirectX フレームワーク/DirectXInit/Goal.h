#pragma once
#include "Quad.h"

class GameScene;
class Goal
	: public Quad
{
public:
	Goal() {}			// コンストラクタ
	~Goal() {}			// デストラクタ

	// オーバーライドした関数
	void Init();		// 初期化処理
	void Update();		// 更新処理

	std::vector<std::string> GetData() const;
	bool SetData(std::vector<std::string> _data);
};
