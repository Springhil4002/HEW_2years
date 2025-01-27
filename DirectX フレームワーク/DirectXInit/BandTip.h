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
	// ���܂�Ă邩
	bool isGrabing = false;

	// �����̎擾
	MOVEDIRECTION MoveDirection() const { return moveDirection; }

	void Update();

	float GetPullLeveL() const { return pullLeveL; }
	void SetPullLeveL(float _pullLeveL) { pullLeveL = fabsf(_pullLeveL); }
};

