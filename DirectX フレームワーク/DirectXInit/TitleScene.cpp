#include "TitleScene.h"
#include "SceneManager.h"

TitleScene::TitleScene()
{
	BackGround.Init("asset/Texture/Future.jpg");	//�w�i��������
	BackGround.SetScale(1280.0f, 720.0f, 0.0f);		//�傫����ݒ�
}

TitleScene::~TitleScene()
{
	BackGround.Uninit();	//�w�i���I��
}

void TitleScene::Update()
{
	input.Update();	//�L�[���͂̔���
	//�G���^�[�L�[����������
	if (input.GetKeyTrigger(VK_2))
	{
		//���݂̃V�[�����uGameScene�v�ɐ؂�ւ���
		SceneManager::ChangeScene(SceneManager::GAME);
	}
}

void TitleScene::Draw()
{
	BackGround.Draw();		//�w�i��`��
}


