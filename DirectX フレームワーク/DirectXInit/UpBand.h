#pragma once
#include <set>
#include <math.h>
#include "Entity.h"
#include "BandTip.h"
class UpBand : public Entity
{
private:
	// 引かれるObject用のタグ
	std::string objectTag;
	// 引っ張れる部分のオブジェクト
	std::set<Quad*> jagged;
	// 引かれるObject達
	std::set<Object*> objects;
	// どんだけ引っ張ってるか度
	float pullLevel;
public:
	int L;

	// コンストラクタ・デストラクタで先端の管理
	UpBand() : L(4) {}
	~UpBand() { }

	void Init();
	void Update();
	void Uninit();

	void Add(Object* _object);
	void Remove(Object* _object);

	// ゲッター・セッター
	void SetLength(int _length);		// bandの引く長さを渡す関数

	float GetPullLevel()				// どれだけ引っ張ってるかを取ってくる関数
	{
		return pullLevel;
	}

	void SetObject(std::string _tag);

	std::vector<std::string> GetData() const;
	bool SetData(std::vector<std::string> _data);
};