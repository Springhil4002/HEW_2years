#pragma once
#include "Object.h"
class Delay : public Object
{
private:
	std::vector<unsigned> signals;
	bool sig;

public:
	Delay() : sig(false) {}
	~Delay() {}

	// 更新処理
	void Update();

	// 説明：任意のフレーム数後に信号を送る
	// 構文：{Delayオブジェクト}->SetSignal({任意のフレーム数})
	// 例文：delay->SetSignal(10 * FPS);
	void SetSignal(unsigned int _frameCount);
	// 説明：送られた信号を受け取る
	// 構文：if({Delayオブジェクト}->GetSignal())
	// 例文：if(delay->GetSignal())
	bool GetSignal() const;
};