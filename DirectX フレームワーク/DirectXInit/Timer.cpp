#include "Timer.h"

//===================================================================
// ����������
//===================================================================
void Timer::Init()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&lastTime);
}

//===================================================================
// �X�V����
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
// �������
//===================================================================
void Timer::Uninit()
{
	delete this;
}