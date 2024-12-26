#pragma once
#include <math.h>
#include "Physic.h"
class BandTip : public Physic
{
public:
	float pullLeveL;
	// ‚Â‚©‚Ü‚ê‚Ä‚é‚©
	bool isGrabing = false;

	// Œü‚«‚ÌŽæ“¾
	MOVEDIRECTION MoveDirection() const { return moveDirection; }

	float GetPullLeveL() const { return pullLeveL; }
	void SetPullLeveL(float _pullLeveL) { pullLeveL = fabsf(_pullLeveL); }
};

