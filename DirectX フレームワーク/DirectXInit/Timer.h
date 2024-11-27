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

	void Init();	// ‰Šú‰»
	void Update();	// XV
	void Uninit();	// ‰ğ•ú
	
	float GetDeltaTime()const { return deltaTime; }	// Œo‰ßŠÔ‚ğÁ‚·
};