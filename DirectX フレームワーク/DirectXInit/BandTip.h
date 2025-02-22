#pragma once
#include <math.h>
#include "Physic.h"

class Band;
class BandTip : public Physic
{
	friend class Band;
private:
	Band* band;

public:
	float pullLeveL;
	// つかまれてるか
	bool isGrabing = false;

	// 向きの取得
	MOVEDIRECTION MoveDirection() const { return moveDirection; }

	void Update();

	float GetPullLeveL() const { return pullLeveL; }
	void SetPullLeveL(float _pullLeveL) { pullLeveL = fabsf(_pullLeveL); }
};

