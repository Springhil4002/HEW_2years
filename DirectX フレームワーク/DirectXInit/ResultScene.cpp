#include "ResultScene.h"
#include "SceneManager.h"
#include "Quad.h"

ResultScene::ResultScene()
{
	//bg.Init("asset/Texture/Night.jpg");		//�w�i��������
	//bg.SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);	//�傫����ݒ�
}

ResultScene::~ResultScene()
{
	SceneManager::m_SoundManager.Uninit();	// �T�E���h�}�l�[�W���[���I��
	//bg.Uninit();	//�w�i���I��
}

void ResultScene::Init()
{
	auto bg = Object::Create<Quad>();
	bg->SetTex("asset/Texture/Night.jpg");
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
}

void ResultScene::Update()
{
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// �T�E���h���Đ�
	//input.Update();	//�L�[���͂̔���
	// "1"�L�[����������
	if (input.GetKeyTrigger(VK_1))
	{
		//���݂̃V�[�����uTitleScene�v�ɐ؂�ւ���
		SceneManager::ChangeScene(SceneManager::TITLE);
	}
}

//void ResultScene::Draw()
//{
//	bg.Draw();		//�w�i��`��
//}
