#pragma once
#include "Quad.h"

class Coin 
	: public Quad
{
public:
	Coin() {}
	~Coin() {}

	void Init();
	void Update();
};

