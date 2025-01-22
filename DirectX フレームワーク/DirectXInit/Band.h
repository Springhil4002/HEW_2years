#pragma once
#include <set>
#include <math.h>
#include "Entity.h"
#include "BandTip.h"
class Band : public Entity
{
private: 
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
public:
	int L;
	
	// コンストラクタ・デストラクタで先端の管理
	Band(): L(4) { tip = Object::Create<BandTip>(); }
	~Band() { Object::Delete(tip); }

	void Init();
	void Update();
	void Uninit();

	void Add(Object* _object);
	void Remove(Object* _object);

	// ゲッター・セッター
	void SetLength(int _length);		// bandの引く長さを渡す関数
								
	float GetPullLevel()				// どれだけ引っ張ってるかを取ってくる関数
	{return pullLevel; }

	std::vector<std::string> GetData() const;
	bool SetData(std::vector<std::string> _data);
};