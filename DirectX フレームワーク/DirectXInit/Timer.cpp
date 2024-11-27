#include "Timer.h"

//===================================================================
// ‰Šú‰»ˆ—
//===================================================================
void Timer::Init()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&lastTime);
}

//===================================================================
// XVˆ—
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
// ‰ğ•úˆ—
//===================================================================
void Timer::Uninit()
{
	delete this;
}