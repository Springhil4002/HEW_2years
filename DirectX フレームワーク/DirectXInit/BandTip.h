#pragma once
#include <math.h>
#include "Physic.h"
class BandTip : public Physic
{
public:
	float pullLeveL;
	// ���܂�Ă邩
	bool isGrabing = false;

	// �����̎擾
	MOVEDIRECTION MoveDirection() const { return moveDirection; }

	float GetPullLeveL() const { return pullLeveL; }
	void SetPullLeveL(float _pullLeveL) { pullLeveL = fabsf(_pullLeveL); }
};

