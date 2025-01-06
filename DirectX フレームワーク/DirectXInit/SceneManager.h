#pragma once
#include "Scene.h"
#include "SoundManager.h"

class SceneManager
{
public:
	//�񋓌^
	enum SCENE {
		TITLE,
		HOME_1,
		HOME_2,
		GAME,
		RESULT
	};

private:	
	static Scene* currentScene;	//���݂̃V�[��
	static SCENE nextScene;
	static bool changed;
	static void NewScene();
public:
	static SoundManager m_SoundManager;	// �V�[���}�l�[�W���[�̃C���X�^���X
	SceneManager() {}		//�R���X�g���N�^
	~SceneManager() {}		//�f�X�g���N�^

	static void Init();		//�����������֐�
	static void Update();	//�X�V�����֐�
	static void Draw();		//�`�揈���֐�
	static void Uninit();	//��������֐�

	static void ChangeScene(SCENE _scene);	//���݂̃V�[����؂�ւ��鏈���֐�
};