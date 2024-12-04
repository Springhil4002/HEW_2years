#pragma once
#include <math.h>
#include <simpleMath.h>
#include "Shader.h"
#include"Tags.h"

class Object {
private:
	static std::vector<Object*>* objInstance;

protected:
	// SRT情報(姿勢情報)
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

	// 描画の為の情報（見た目に関わる部分）
	static Shader m_Shader; // シェーダー

	// タグ
	Tags tags;


public:	
	Object() { objInstance = new std::vector<Object*>; }
	~Object() { delete objInstance; }

	// 純粋仮想関数
	virtual void Init() {}	// 初期化処理
	virtual void Update() = 0;	// 更新処理
	virtual void Draw() = 0;	// 描画処理
	virtual void Uninit() = 0;	// 解放処理

	// 各種セッター
	void SetPos(float _x, float _y, float _z);				//座標をセット
	void SetRotation(float _x, float _y, float _z);			//角度をセット
	void SetScale(float _x, float _y, float _z);			//大きさをセット

	// タグ検索
	bool SearchTag(const std::string _tag) const;

	static void CreateShader();
	static std::vector<Object*>* GetInstance();

	// その型のオブジェクトを返すぜ
	template<class T>
	static std::vector<T*> GetObj()
	{
		// 返すやつ
		std::vector<T*> ret;

		// 全オブジェクトから探そう
		for (auto& all : *Object::GetInstance())
		{
			// ダイナミックキャストしてあるならretにいれる
			T* obj = dynamic_cast<T*>(all);
			if (obj != nullptr)
			{
				ret.push_back(obj);
			}
		}
		return ret;
	}

	// 2つのオブジェクトの衝突判定
	static bool Collision(Object* _object1, Object* _object2);
};