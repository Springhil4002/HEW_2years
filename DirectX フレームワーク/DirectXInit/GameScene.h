#pragma once
#include "Scene.h"

#define OBJECT_X_VALUE		(32)
#define OBJECT_Y_VALUE		(18)
#define GROUND_OFFSET_X		(-930.0f)
#define GROUND_OFFSET_Y		(-510.0f)
#define SCENE_ENUM_OFFSET	(3)

class GameScene : public Scene
{
private:
	int gameSceneNum = 0;	// GameScene(ステージ)の識別用番号
public:
	GameScene(int _num)		//コンストラクタ
	{ Init(_num); };	
	~GameScene() {};		//デストラクタ

	void Init(int _num);	// 基本的に初期化はこっち使う

	//オーバーライドした関数
	void Init() {};			// 初期化処理関数
	void Update();			// 更新処理関数
};