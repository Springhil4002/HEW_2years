#pragma once
#include "Quad.h"
class BandTip :
    public Quad
{
public:
	// ‚Â‚©‚Ü‚ê‚Ä‚é‚©
	bool isGrabing = false;

	// Œü‚«‚Ìæ“¾
	MOVEDIRECTION MoveDirection() const { return moveDirection; }

	// xÀ•W‚Ìæ“¾
	float GetPosX() const;
};

