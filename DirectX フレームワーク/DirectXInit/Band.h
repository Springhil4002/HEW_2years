#pragma once
#include <set>
#include <math.h>
#include "Entity.h"
#include "BandTip.h"
#include "Delay.h"

class Band : public Entity
{
	friend class BandTip;
private: 
	enum Status
	{
		DEFAULT,
		STOP,
		LIMIT,
		REVERSE
	};

	// バンドの状態
	Status status;
	// 引かれるObject用のタグ
	std::string objectTag;
	// 先端のインスタンス
	BandTip* tip;
	// ギザギザ部分のインスタンス
	std::set<Quad*> jagged;
	// 引かれるObject達
	std::set<Object*> objects;
	// どんだけ引っ張ってるか度
	float pullLevel;
	// 前の座標
	DirectX::SimpleMath::Vector3 oldPos;
	
	Delay* delay;
	bool sendDelay;
public:
	int L;
	
	// コンストラクタ・デストラクタで先端の管理
	Band();
	~Band() {  }

	void Init();
	void Update();
	void Uninit();

	void Add(Object* _object);
	void Remove(Object* _object);

	// ゲッター・セッター
	void SetLength(int _length);		// bandの引く長さを渡す関数
								
	float GetPullLevel()				// どれだけ引っ張ってるかを取ってくる関数
	{return pullLevel; }

	void SetObject(std::string _tag);
	void ResetObject();

	std::vector<std::string> GetData() const;
	bool SetData(std::vector<std::string> _data);
};