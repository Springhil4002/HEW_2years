#pragma once
class Scene;

class SceneManager
{
private:
	static Scene* currentScene;	//現在のシーン

public:
	//列挙型
	enum SCENE {
		TITLE,
		GAME,
		RESULT
	};

	static void ChangeScene(SCENE _scene);	//現在のシーンを切り替える処理関数
	static void Update();	//更新処理関数
	static void Draw();		//描画処理関数
	static void Uninit();	//解放処理関数
};