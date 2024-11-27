#pragma once

#include <Windows.h>

class Timer
{
private:
	static LARGE_INTEGER frequency;
	static LARGE_INTEGER lastTime;
	float deltaTime;
public:
	~Timer() = default;

	void Init();	// 初期化
	void Update();	// 更新
	void Uninit();	// 解放
	
	float GetDeltaTime()const { return deltaTime; }	// 経過時間を消す
};