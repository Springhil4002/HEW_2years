#pragma once
#include <math.h>
#include <simpleMath.h>
#include"Tags.h"
#include"Scene.h"

class Object {
protected:
	// SRT情報(姿勢情報)
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

public:	
	// レイヤー
	int layer;

	// タグ
	Tags tags;
	
	Object() {}
	~Object() {}

	virtual void Init() {}		// 初期化処理
	virtual void Update() {};	// 更新処理
	virtual void Draw() {};		// 描画処理
	virtual void Uninit() {};	// 解放処理

	// 各種セッター
	void SetPos(float _x, float _y, float _z);				//座標をセット
	void SetRotation(float _x, float _y, float _z);			//角度をセット
	void SetScale(float _x, float _y, float _z);			//大きさをセット

	DirectX::SimpleMath::Vector3 GetPos() const;

	// オブジェクトの生成
	template<class T>
	static T* Create()
	{
		T* buf = new T;
		Scene::GetInstance()->GetObjects()->insert(buf);
		return buf;
	}

	// オブジェクトの削除
	static void Delete(Object* _object);

	// 2つのオブジェクトの衝突判定
	static bool Collision(Object* _object1, Object* _object2);
};