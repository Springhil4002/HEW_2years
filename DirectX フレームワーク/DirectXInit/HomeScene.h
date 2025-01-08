#pragma once
#include "Scene.h"

class HomeScene
	: public Scene
{
private:
	//Quad bg;	// 背景オブジェクト
	//std::vector <std::unique_ptr<Object>>objects;	// オブジェクト配列
	int homeSceneNum = 0;	// HomeSceneの切り替え用の番号
	int frameNum = 0;		// frameの識別用番号
public:
	HomeScene(int _num);		// コンストラクタ(初期化処理)
	~HomeScene();		// デストラクタ	(解放処理)

	//オーバーライドした関数
	void Init() {};
	void Init(int _num);
	void Update();		// 更新処理
	//void Draw();		// 描画処理
};