#pragma once
#include "Scene.h"

class HomeScene
	: public Scene
{
private:
	int homeSceneNum = 0;	// HomeSceneの切り替え用の番号
	int frameNum = 0;		// frameの識別用番号
public:
	HomeScene(int _num);	// コンストラクタ(初期化処理)
	~HomeScene() {};		// デストラクタ	(解放処理)

	void Init(int _num);	// 基本的に初期化処理はこっち使う

	//オーバーライドした関数
	void Init() {};			// 初期化処理
	void Update();			// 更新処理
};