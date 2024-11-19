#pragma once

#include "Component.h"

class Transform :public Component
{
private:
	// SRT情報(姿勢情報)
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
public:
	// オーバーライドした関数
	void Start();	// 初期化処理
	void Update();	// 更新処理
	void Draw();	// 描画処理

	// 各種セッター
	void SetPos(float _x, float _y, float _z);				//座標をセット
	void SetRotation(float _x, float _y, float _z);			//角度をセット
	void SetScale(float _x, float _y, float _z);			//大きさをセット
};

