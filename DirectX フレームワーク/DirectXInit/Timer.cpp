#include "Timer.h"

//===================================================================
// 初期化処理
//===================================================================
void Timer::Init()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&lastTime);
}

//===================================================================
// 更新処理
//===================================================================
void Timer::Update()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	deltaTime = static_cast<float>
		(currentTime.QuadPart - lastTime.QuadPart) / frequency.QuadPart;
	lastTime = currentTime;
}

//===================================================================
// 解放処理
//===================================================================
void Timer::Uninit()
{
	delete this;
}