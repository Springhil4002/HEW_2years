#pragma once
#include "Physic.h"
class BandTip : public Physic
{
public:
	// つかまれてるか
	bool isGrabing = false;

	// 向きの取得
	MOVEDIRECTION MoveDirection() const { return moveDirection; }
};

