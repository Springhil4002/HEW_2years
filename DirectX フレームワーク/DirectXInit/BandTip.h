#pragma once
#include "Physic.h"
class BandTip : public Physic
{
public:
	// ���܂�Ă邩
	bool isGrabing = false;

	// �����̎擾
	MOVEDIRECTION MoveDirection() const { return moveDirection; }
};

