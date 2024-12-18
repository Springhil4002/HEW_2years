#pragma once
#include "Physic.h"
class BandTip : public Physic
{
public:
	// ‚Â‚©‚Ü‚ê‚Ä‚é‚©
	bool isGrabing = false;

	// Œü‚«‚ÌŽæ“¾
	MOVEDIRECTION MoveDirection() const { return moveDirection; }
};

