#pragma once
#include <Windows.h>

class Cursor
{
private:
	static int x;
	static int y;

public:
	static void Update(LPARAM _lP);
	static int GetX();
	static int GetY();
};

