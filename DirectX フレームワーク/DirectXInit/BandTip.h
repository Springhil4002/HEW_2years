#pragma once
#include <math.h>
#include "Physic.h"
class BandTip : public Physic
{
public:
	float pullLeveL;
	// つかまれてるか
	bool isGrabing = false;

	// 向きの取得
	MOVEDIRECTION MoveDirection() const { return moveDirection; }

	float GetPullLeveL() const { return pullLeveL; }
	void SetPullLeveL(float _pullLeveL) { pullLeveL = fabsf(_pullLeveL); }
};

