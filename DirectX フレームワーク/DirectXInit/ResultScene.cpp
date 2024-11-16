#include "ResultScene.h"
#include "SceneManager.h"

ResultScene::ResultScene()
{
	BackGround.Init("asset/Texture/Night.jpg");		//�w�i��������
	BackGround.SetScale(1280.0f, 720.0f, 0.0f);	//�傫����ݒ�
}

ResultScene::~ResultScene()
{
	BackGround.Uninit();	//�w�i���I��
}

void ResultScene::Update()
{
	input.Update();	//�L�[���͂̔���
	//�G���^�[�L�[����������
	if (input.GetKeyTrigger(VK_1))
	{
		//���݂̃V�[�����uTitleScene�v�ɐ؂�ւ���
		SceneManager::ChangeScene(SceneManager::TITLE);
	}
}

void ResultScene::Draw()
{
	BackGround.Draw();		//�w�i��`��
}
