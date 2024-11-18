#pragma once

#include "Object.h"
#include "Com_Transform.h"
#include "Com_Quad.h"

class Object;

class Component
{
public:
	Component(){}				// コンストラクタ
	virtual ~Component() {}		// デストラクタ

	// コンポーネントが属する親オブジェクトを指すポインタ
	Object* Parent;				

	// 純粋仮想関数
	virtual void Start(){}		// 初期化処理		
	virtual void Update(){}		// 更新処理
	virtual void Draw(){}		// 描画処理
};