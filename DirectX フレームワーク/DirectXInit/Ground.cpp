#include "Ground.h"

using namespace DirectX::SimpleMath;

//===================================================================
// 初期化処理
//===================================================================
void Ground::Init()
{
	SetTex("asset/Texture/ground.png");
	// SetTex("asset/Texture/Ground_Object.png");
	// オブジェクトのサイズ設定
	SetScale(60.0f, 60.0f, 0.0f);
}

std::vector<std::string> Ground::GetData() const
{
	std::vector<std::string> buf;
	buf.push_back("Ground");
	auto objectData = Object::GetData();
	buf.insert(buf.end(), objectData.begin(), objectData.end());
	return buf;
}

bool Ground::SetData(std::vector<std::string> _data)
{
	if (_data.front() == "Ground")
	{
		std::vector<std::string> objBuf(_data.size());
		std::copy(_data.begin() + 1, _data.end(), objBuf.begin());
		Object::SetData(objBuf);

		return true;
	}
	else
	{
		return false;
	}
}