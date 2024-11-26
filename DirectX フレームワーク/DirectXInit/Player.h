#pragma once
#include "Input.h"
#include "Quad.h"

class Player :Quad {
protected:
	Input input;
public:
	void Walk();
};