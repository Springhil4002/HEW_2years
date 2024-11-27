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

	void Init();	// ������
	void Update();	// �X�V
	void Uninit();	// ���
	
	float GetDeltaTime()const { return deltaTime; }	// �o�ߎ��Ԃ�����
};