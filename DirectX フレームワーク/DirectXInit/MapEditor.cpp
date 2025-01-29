#include "MapEditor.h"
#include "Cursor.h"
#include "Ground.h"
#include "Band.h"
#include "Goal.h"
#include "Coin.h"
#include "main.h"
#include "UpBand.h"
#include <iostream>


Quad* MapEditor::cursor = nullptr;
CSV MapEditor::mapData;

void MapEditor::Init()
{	
	cursor = Object::Create<Quad>();
	cursor->SetTex("asset/Texture/Ground.png");
	cursor->SetPos(0.0f, 0.0f, 0.0f);
	cursor->SetScale(60.0f, 60.0f, 0.0f);

	Load("TEST10_STAGE2.csv");

	//auto katen = Object::Create<Quad>();
	//katen->SetTex("asset/Texture/Band_Block.png");
	//katen->SetPos(BLOCK_SIZE * 8.5f, BLOCK_SIZE * -1, 0.0f);
	//katen->SetScale(BLOCK_SIZE * 5, BLOCK_SIZE * 4, 0.0f);
	//katen->layer = -1;
	//katen->tags.AddTag("BandD");

	//for (auto& obj : SceneManager::ListCreate())
	//{
	//	if (dynamic_cast<Ground*>(obj) != nullptr || dynamic_cast<Band*>(obj) != nullptr || dynamic_cast<UpBand*>(obj) != nullptr)
	//	{
	//		if (Object::Collision(obj, katen))
	//		{
	//			obj->tags.AddTag("BandD");
	//		}
	//	}
	//}

	//Object::Delete(katen);
}

void MapEditor::Update()
{	
	auto objects = objectInstance;
	for (auto& obj : objects)
	{
		obj->Update();
	}

	int x = Cursor::GetX() - Cursor::GetX() % 60 - (int)SCREEN_WIDTH / 2;
	int y = -(Cursor::GetY() - Cursor::GetY() % 60 - (int)SCREEN_HEIGHT / 2);

	switch (select)
	{
	case PLAYER:
		x += 30;
		break;
	case GROUND:
		x += 30;
		y -= 30;
		break;
	case BAND:
		x += 30;
		y -= 30;
		break;
	case UPBAND:
		x += 30;
		y -= 30;
		break;
	case GOAL:
		x += 30;
		break;
	case COIN:
		x += 30;
		y -= 30;
		break;
	}

	cursor->SetPos(x, y, 0);

	if (input.GetKeyTrigger(VK_RIGHT))
	{
		if (select < ObjectType::MAX - 1)
		{
			select++;
		}
		else
		{
			select = 0;
		}
	}

	if (input.GetKeyTrigger(VK_LEFT))
	{
		if (select > 0)
		{
			select--;
		}
		else
		{
			select = ObjectType::MAX - 1;
		}
	}

	switch (select)
	{
	case PLAYER:
		cursor->SetTex("asset/Texture/player.png");
		cursor->SetScale(60.0f, 120.0f, 0.0f);
		cursor->SetRotation(0,0,0);
		break;
	case GROUND:
		cursor->SetTex("asset/Texture/ground.png");
		cursor->SetScale(60.0f, 60.0f, 0.0f);
		cursor->SetRotation(0, 0, 0);
		break;
	case BAND:
		cursor->SetTex("asset/Texture/Band_Tip.png");
		cursor->SetScale(60.0f, 60.0f, 0.0f);
		cursor->SetRotation(0, 0, 0);
		break;
	case UPBAND:
		cursor->SetTex("asset/Texture/Band_Tip.png");
		cursor->SetScale(60.0f, 60.0f, 0.0f);
		cursor->SetRotation(0, 0, -3.14f / 2);
		break;
	case GOAL:
		cursor->SetTex("asset/Texture/Door.png");
		cursor->SetScale(60.0f, 120.0f, 0.0f);
		cursor->SetRotation(0, 0, 0);
		break;
	case COIN:
		cursor->SetTex("asset/Texture/Coin.png");
		cursor->SetScale(60.0f, 60.0f, 0.0f);
		cursor->SetRotation(0, 0, 0);
		break;
	}


	if (input.GetKeyTrigger(VK_LBUTTON))
	{
		bool flg = true;
		auto objects = objectInstance;
		objects.erase(cursor);
		for (auto& obj : objects)
		{
			if (Object::Collision(obj, cursor))
			{
				Object::Delete(obj);
				flg = false;
				break;
			}
		}

		if (flg)
		{
			switch (select)
			{
			case PLAYER:
			{
				auto player = Object::Create<Player>();
				player->SetPos(x, y, 0);
			}
				break;
			case GROUND:
			{
				auto ground = Object::Create<Ground>();
				ground->SetPos(x, y, 0);
			}
				break;
			case BAND:
			{
				auto band = Object::Create<Band>();
				band->SetPos(x, y, 0);

				std::cout << "バンド名を入力してください" << std::endl;
				std::string bufStr;
				std::cin >> bufStr;
				band->SetObject(bufStr);
				std::cout << "バンド名「" +bufStr + "」を保存しました" << std::endl;
				std::cout << "バンドの長さを入力してください" << std::endl;
				std::cin >> bufStr;
				band->SetLength(stoi(bufStr));
				std::cout << "バンドの長さを" + bufStr + "マスで保存しました" << std::endl;
			}
			break;
			case UPBAND:
			{
				auto upBand = Object::Create<UpBand>();
				upBand->SetPos(x, y, 0);

				std::cout << "バンド名を入力してください" << std::endl;
				std::string bufStr;
				std::cin >> bufStr;
				std::cout << "バンド名「" + bufStr + "」を保存しました" << std::endl;
				std::cout << "バンドの長さを入力してください" << std::endl;
				upBand->SetObject(bufStr);
				std::cin >> bufStr;
				upBand->L = stoi(bufStr);
				std::cout << "バンドの長さを" + bufStr + "マスで保存しました" << std::endl;
			}
			break;
			case GOAL:
			{
				auto goal = Object::Create<Goal>();
				goal->SetPos(x, y, 0);
			}
				break;
			case COIN:
			{
				auto goal = Object::Create<Coin>();
				goal->SetPos(x, y, 0);
			}
			break;

			}
		}
	}

	if (input.GetKeyTrigger(VK_RBUTTON))
	{
		auto objects = objectInstance;
		objects.erase(cursor);
		for (auto& obj : objects)
		{
			if (Object::Collision(obj, cursor))
			{
				std::cout << "タグ名を入力してください" << std::endl;
				std::string bufTag;
				std::cin >> bufTag;
				obj->tags.AddTag(bufTag);
				std::cout << "タグ「" + bufTag + "」を保存しました" << std::endl;
				break;
			}
		}
	}

	if (input.GetKeyPress(VK_CONTROL) && input.GetKeyTrigger(VK_S))
	{
		std::cout << "セーブするファイルの名前(.csv)を入力してください" << std::endl;
		std::string bufName;
		std::cin >> bufName;
		Save(bufName);
		std::cout << "ファイル名「" + bufName + "」をセーブしました" << std::endl;
	}

	if (input.GetKeyPress(VK_CONTROL) && input.GetKeyTrigger(VK_L))
	{
		std::cout << "ロードするファイルの名前(.csv)を入力してください" << std::endl;
		std::string bufName;
		std::cin >> bufName;
		Load(bufName);
		std::cout << "ファイル名「" + bufName + "」をロードしました" << std::endl;
	}

	//if (input.GetKeyTrigger(VK_P))
	//{
	//	player = Object::Create<Player>();
	//	player->layer = 1;
	//}

	//if (input.GetKeyRelease(VK_P))
	//{
	//	Object::Delete(player);
	//}
}

void MapEditor::Save(std::string _fileName_csv)
{
	mapData.clear();

	auto gnds = Scene::GetInstance()->GetObjects<Ground>();
	auto gols = Scene::GetInstance()->GetObjects<Goal>();
	auto bnds = Scene::GetInstance()->GetObjects<Band>();
	auto ubds = Scene::GetInstance()->GetObjects<UpBand>();
	auto plys = Scene::GetInstance()->GetObjects<Player>();
	auto cons = Scene::GetInstance()->GetObjects<Coin>();

	for (auto& gnd : gnds)
	{
		mapData.push_back(gnd->GetData());
	}
	for (auto& gol : gols)
	{
		mapData.push_back(gol->GetData());
	}
	for (auto& con : cons)
	{
		mapData.push_back(con->GetData());
	}
	for (auto& ply : plys)
	{
		mapData.push_back(ply->GetData());
	}
	for (auto& bnd : bnds)
	{
		mapData.push_back(bnd->GetData());
	}
	for (auto& ubd : ubds)
	{
		mapData.push_back(ubd->GetData());
	}

	mapData.Save(_fileName_csv);
}

bool MapEditor::Load(std::string _fileName_csv)
{
	mapData.Load(_fileName_csv);

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
		else if (objData.front() == "Band")
		{
			object = Object::Create<Band>();
		}
		else if (objData.front() == "UpBand")
		{
			object = Object::Create<UpBand>();
		}
		else if (objData.front() == "Goal")
		{
			object = Object::Create<Goal>();
		}
		else if (objData.front() == "Coin")
		{
			object = Object::Create<Coin>();
		}
		else if (objData.front() == "Entity")
		{
			object = Object::Create<Entity>();
		}
		else if (objData.front() == "Player")
		{
			object = Object::Create<Player>();
		}
		else
		{
			printf("error:読込データがバグってるよ\n");
			break;
		}

		object->SetData(objData);
	}

	return true;
}