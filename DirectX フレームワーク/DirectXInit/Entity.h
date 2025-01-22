#pragma once
#include"Physic.h"
#include"Scene.h"

class Entity : public Physic
{
public:
	Entity() {}
	~Entity() {}

	void Update();

	std::vector<std::string> GetData() const;
	bool SetData(std::vector<std::string> _data);
};

