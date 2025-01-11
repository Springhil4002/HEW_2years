#include "MapEditor.h"
#include "Cursor.h"
#include "Ground.h"
#include "main.h"

void MapEditor::Init()
{
	logo = Object::Create<Quad>();
	logo->SetTex("asset/Texture/Ground.png");
	logo->SetPos(0.0f, 0.0f, 0.0f);
	logo->SetScale(60.0f, 60.0f, 0.0f);
}

void MapEditor::Update()
{
	int x = Cursor::GetX() - Cursor::GetX() % 60 - (int)SCREEN_WIDTH / 2 + 30;
	int y = -(Cursor::GetY() - Cursor::GetY() % 60 - (int)SCREEN_HEIGHT / 2 + 30);

	logo->SetPos(x, y, 0);
	if (input.GetKeyTrigger(VK_LBUTTON))
	{
		auto ground = Object::Create<Ground>();
		ground->SetPos(x, y, 0);
	}


}