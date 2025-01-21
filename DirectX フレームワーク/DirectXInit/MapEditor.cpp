#include "MapEditor.h"
#include "Cursor.h"
#include "Ground.h"
#include "Band.h"
#include "main.h"

Quad* MapEditor::cursor = nullptr;
CSV MapEditor::mapData;

void MapEditor::Init()
{
	cursor = Object::Create<Quad>();
	cursor->SetTex("asset/Texture/Ground.png");
	cursor->SetPos(0.0f, 0.0f, 0.0f);
	cursor->SetScale(60.0f, 60.0f, 0.0f);
}

void MapEditor::Update()
{
	auto objects = objectInstance;
	for (auto& obj : objects)
	{
		obj->Update();
	}

	int x = Cursor::GetX() - Cursor::GetX() % 60 - (int)SCREEN_WIDTH / 2 + 30;
	int y = -(Cursor::GetY() - Cursor::GetY() % 60 - (int)SCREEN_HEIGHT / 2 + 30);

	cursor->SetPos(x, y, 0);
	if (input.GetKeyTrigger(VK_LBUTTON))
	{
		bool flg = true;
		auto objects = objectInstance;
		objects.erase(cursor);
		for (auto& obj : objects)
		{
			if (obj->GetPos() == DirectX::SimpleMath::Vector3(x, y, 0))
			{
				Object::Delete(obj);
				flg = false;
				break;
			}
		}

		if (flg)
		{
			auto ground = Object::Create<Band>();
			ground->SetPos(x, y, 0);
			ground->SetTex("asset/Texture/ground.png");
			ground->SetScale(60, 60, 0);
		}
	}

	if (input.GetKeyTrigger(VK_S))
	{
		Save("MapData.csv");
	}

	if (input.GetKeyTrigger(VK_L))
	{
		Load("MapData.csv");
	}

	if (input.GetKeyTrigger(VK_P))
	{
		player = Object::Create<Player>();
		player->layer = 1;
	}

	if (input.GetKeyRelease(VK_P))
	{
		Object::Delete(player);
	}
}

void MapEditor::Save(std::string _fileName_csv)
{
	auto objs = *Scene::GetInstance()->GetObjects();
	objs.erase(cursor);
	unsigned int cnt = 0;
	for (auto& obj : objs)
	{
		std::vector<std::string> buf;
		mapData.push_back(obj->GetData());
		cnt++;
	}

	mapData.Save("MapData.csv");
}

bool MapEditor::Load(std::string _fileName_csv)
{
	mapData.Load("MapData.csv");

	auto objects = *Scene::GetInstance()->GetObjects();
	objects.erase(cursor);
	for (auto& obj : objects)
		Object::Delete(obj);	
	
	for (auto& objData : mapData)
	{
		Object* object = nullptr;
		if (objData.front() == "Ground")
		{
			object = Object::Create<Ground>();
		}
		if (objData.front() == "Band")
		{
			object = Object::Create<Band>();
		}
		if (objData.front() == "Object")
		{
			break;
		}

		object->SetData(objData);
	}

	return true;
}