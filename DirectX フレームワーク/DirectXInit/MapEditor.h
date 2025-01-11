#pragma once
#include "Scene.h"
#include "Quad.h"
class MapEditor : public Scene
{
private:
	Quad* logo;

public:
	MapEditor() : logo(nullptr) {}
	~MapEditor() {}

	void Init();
	void Update();
};

