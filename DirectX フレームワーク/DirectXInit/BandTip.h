#pragma once
#include "Quad.h"
class BandTip :
    public Quad
{
public:
	// ���܂�Ă邩
	bool isGrabing = false;

	// �����̎擾
	MOVEDIRECTION MoveDirection() const { return moveDirection; }

	// x���W�̎擾
	float GetPosX() const;
};

