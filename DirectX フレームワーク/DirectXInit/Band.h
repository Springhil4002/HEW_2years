#pragma once
#include "Entity.h"
#include "BandTip.h"
class Band : public Entity
{
private:
	// 先端のインスタンス
	BandTip* tip;

public:
	// コンストラクタ・デストラクタで先端の管理
	Band() { tip = Object::Create<BandTip>(); }
	~Band() { Object::Delete(tip); }

public:
	void Init();
	void Update();
};

