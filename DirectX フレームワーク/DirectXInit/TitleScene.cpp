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
	//bg.Uninit();	// �w�i���I��
}

void TitleScene::Init()
{
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM003);	// �T�E���h��~
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM001);	// �T�E���h�Đ�
	auto bg = Object::Create<Quad>();
	auto buttonLogo = Object::Create<Quad>();
	auto titleLogo = Object::Create<Quad>();
	bg->SetTex("asset/Texture/Future.jpg");
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);			//�傫����ݒ�
	buttonLogo->SetTex("asset/Texture/Start_Logo.png");
	buttonLogo->SetPos(0.0f, -300.0f, 0.0f);				//���W��ݒ�
	buttonLogo->SetScale(600.0f, 200.0f, 0.0f);				//�傫����ݒ�
	titleLogo->SetTex("asset/Texture/Title_Logo.png");		
	titleLogo->SetPos(0.0f, 200.0f, 0.0f);					//���W��ݒ�
	titleLogo->SetScale(800.0f, 350.0f, 0.0f);				//�傫����ݒ�
}

void TitleScene::Update()
{
	// �G���^�[�L�[orB�{�^������������
	if (input.GetKeyTrigger(VK_RETURN)||
		input.GetButtonTrigger(XINPUT_B))
	{
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
		//���݂̃V�[�����uGameScene�v�ɐ؂�ւ���
		SceneManager::ChangeScene(SceneManager::HOME_1);
	}
}

//void TitleScene::Draw()
//{
//	bg.Draw();		// �w�i��`��
//}