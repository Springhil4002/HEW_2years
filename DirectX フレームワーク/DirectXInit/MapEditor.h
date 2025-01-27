#pragma once
#include "Scene.h"
#include "Quad.h"
#include "CSV.h"
#include "Player.h"

class MapEditor : public Scene
{
private:
	enum ObjectType
	{
		PLAYER,
		GROUND,
		BAND,
		UPBAND,
		GOAL,
		COIN,



		MAX
	};

	int select;

	static CSV mapData;
	static Quad* cursor;
public:
	MapEditor() : select(PLAYER) {}
	~MapEditor() {}

	void Init();
	void Update();

	static void Save(std::string _fileName_csv);
	static bool Load(std::string _fileName_csv);
};

