#pragma once
#include"Scene.h"

class SceneManager
{
public:
	//�񋓌^
	enum SCENE {
		TITLE,
		GAME,
		RESULT
	};

private:	
	static Scene* currentScene;	//���݂̃V�[��
	static SCENE nextScene;
	static bool changed;

	static void NewScene();

public:
	SceneManager() {}		//�R���X�g���N�^
	~SceneManager() {}		//�f�X�g���N�^

	static void Init();		//�����������֐�
	static void Update();	//�X�V�����֐�
	static void Draw();		//�`�揈���֐�
	static void Uninit();	//��������֐�

	static void ChangeScene(SCENE _scene);	//���݂̃V�[����؂�ւ��鏈���֐�
};