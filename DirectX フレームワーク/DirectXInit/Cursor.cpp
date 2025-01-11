#include "Cursor.h"
#include<windowsx.h>
int Cursor::x = 0;
int Cursor::y = 0;

void Cursor::Update(LPARAM _lP)
{
	x = GET_X_LPARAM(_lP);
	y = GET_Y_LPARAM(_lP);
}

int Cursor::GetX()
{
	return x;
}

int Cursor::GetY()
{
	return y;
}