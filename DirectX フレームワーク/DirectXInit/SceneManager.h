#pragma once
#include"Object.h"
class Scene;

class SceneManager
{
private:
	static Scene* currentScene;	//���݂̃V�[��


public:
	//�񋓌^
	enum SCENE {
		TITLE,
		GAME,
		RESULT
	};

	static void ChangeScene(SCENE _scene);	//���݂̃V�[����؂�ւ��鏈���֐�
	static void Init();
	static void Update();	//�X�V�����֐�
	static void Draw();		//�`�揈���֐�
	static void Uninit();	//��������֐�
};