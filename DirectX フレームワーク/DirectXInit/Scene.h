#pragma once
#include <stdio.h>
#include "input.h"
#include "Object.h"
#include "Quad.h"
#include "Ground.h"
#include "Player.h"
#include "Physic.h"

#define BACKGROUND_X (1920)
#define BACKGROUND_Y (1080)
#define BLOCK_SIZE	(60.0f)

class Scene
{
protected:
	Input input;		//入力系インスタンス
public:
	Scene();			//コンストラクタ(初期化処理関数)
	virtual ~Scene();	//デストラクタ	(解放処理関数)

	//純粋仮想関数
	virtual void Update() = 0;	//更新処理関数
	virtual void Draw() = 0;	//描画処理関数
};