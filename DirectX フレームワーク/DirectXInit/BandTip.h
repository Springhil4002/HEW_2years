#pragma once
#include "Quad.h"
class BandTip :
    public Quad
{
public:
	// つかまれてるか
	bool isGrabing = false;

	// 向きの取得
	MOVEDIRECTION MoveDirection() const { return moveDirection; }

	// x座標の取得
	float GetPosX() const;
};

