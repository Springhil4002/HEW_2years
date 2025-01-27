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
	// ‚Â‚©‚Ü‚ê‚Ä‚é‚©
	bool isGrabing = false;

	// Œü‚«‚ÌŽæ“¾
	MOVEDIRECTION MoveDirection() const { return moveDirection; }

	void Update();

	float GetPullLeveL() const { return pullLeveL; }
	void SetPullLeveL(float _pullLeveL) { pullLeveL = fabsf(_pullLeveL); }
};

