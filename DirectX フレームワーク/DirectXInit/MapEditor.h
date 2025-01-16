#pragma once
#include "Scene.h"
#include "Quad.h"
#include "CSV.h"
#include "Player.h"

class MapEditor : public Scene
{
private:
	Player* player;

	static CSV mapData;
	static Quad* cursor;
public:
	MapEditor() : player(nullptr) {}
	~MapEditor() {}

	void Init();
	void Update();

	static void Save(std::string _fileName_csv);
	static bool Load(std::string _fileName_csv);
};

