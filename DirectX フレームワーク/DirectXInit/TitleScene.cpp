#include "TitleScene.h"
#include "SceneManager.h"
#include "Quad.h"

TitleScene::TitleScene()
{
	//bg.Init("asset/Texture/Future.jpg");	//�w�i��������
	//bg.SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);		//�傫����ݒ�
}

TitleScene::~TitleScene()
{
	SceneManager::m_SoundManager.Uninit();	// �T�E���h�}�l�[�W���[���I��
	//bg.Uninit();	// �w�i���I��
}

void TitleScene::Init()
{
	auto bg = Object::Create<Quad>();
	bg->SetTex("asset/Texture/Future.jpg");
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);		//�傫����ݒ�
}

void TitleScene::Update()
{
	//input.Update();	//�L�[���͂̔���
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM001);	// �T�E���h�Đ�
	// "2"�L�[����������
	if (input.GetKeyTrigger(VK_2))
	{
		//���݂̃V�[�����uGameScene�v�ɐ؂�ւ���
		SceneManager::ChangeScene(SceneManager::GAME);
	}
}

//void TitleScene::Draw()
//{
//	bg.Draw();		// �w�i��`��
//}