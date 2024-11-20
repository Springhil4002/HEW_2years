#include "TitleScene.h"
#include "SceneManager.h"

TitleScene::TitleScene()
{
	bg.Init("asset/Texture/Future.jpg");	//�w�i��������
	bg.SetScale(1280.0f, 720.0f, 0.0f);		//�傫����ݒ�

	// �z��̗v�f�ɃI�u�W�F�N�g��ǉ�
	objects.emplace_back(new Ground);

	// �I�u�W�F�N�g������
	for (auto& o : objects) {
		o->Init();
	}
}

TitleScene::~TitleScene()
{
	bg.Uninit();	// �w�i���I��
	
	// �I�u�W�F�N�g�I������
	for (auto& o : objects) {
		o->Uninit();
	}
}

void TitleScene::Update()
{
	input.Update();	//�L�[���͂̔���
	
	// �I�u�W�F�N�g�X�V
	for (auto& o : objects) {
		o->Update();
	}

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
	//ground.Draw();	// �n�ʂ�`��
	
	// �I�u�W�F�N�g�`��
	for (auto& o : objects) {
		o->Draw();
	}
}