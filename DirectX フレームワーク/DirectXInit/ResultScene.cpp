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
	//bg.Uninit();	//�w�i���I��
}

void ResultScene::Init()
{
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// �T�E���h���~
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// �T�E���h���Đ�
	auto bg = Object::Create<Quad>();
	bg->SetTex("asset/Texture/Night.jpg");
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
}

void ResultScene::Update()
{
	//input.Update();	//�L�[���͂̔���
	// "1"�L�[����������
	if (input.GetKeyTrigger(VK_1))
	{
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
		//���݂̃V�[�����uTitleScene�v�ɐ؂�ւ���
		SceneManager::ChangeScene(SceneManager::TITLE);
	}
}

//void ResultScene::Draw()
//{
//	bg.Draw();		//�w�i��`��
//}
