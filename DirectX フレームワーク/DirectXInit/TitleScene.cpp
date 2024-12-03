#include "TitleScene.h"
#include "SceneManager.h"

TitleScene::TitleScene()
{
	bg.Init("asset/Texture/Future.jpg");	//�w�i��������
	bg.SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);		//�傫����ݒ�
}

TitleScene::~TitleScene()
{
	bg.Uninit();	// �w�i���I��
}

void TitleScene::Update()
{
	input.Update();	//�L�[���͂̔���
	
	// "2"�L�[����������
	if (input.GetKeyTrigger(VK_2))
	{
		//���݂̃V�[�����uGameScene�v�ɐ؂�ւ���
		SceneManager::ChangeScene(SceneManager::GAME);
	}

	// "3"�L�[����������
	if (input.GetKeyTrigger(VK_3))
	{
		//���݂̃V�[�����uGameScene�v�ɐ؂�ւ���
		SceneManager::ChangeScene(SceneManager::RESULT);
	}
}

void TitleScene::Draw()
{
	bg.Draw();		// �w�i��`��
}