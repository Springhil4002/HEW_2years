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

	std::vector<std::string> GetData() const;
	bool SetData(std::vector<std::string> _data);
};

