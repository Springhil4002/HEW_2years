#pragma once
#include"Physic.h"
#include"Scene.h"

class Entity : public Physic
{
public:
	Entity() {}
	~Entity() {}

	void Update();
};

