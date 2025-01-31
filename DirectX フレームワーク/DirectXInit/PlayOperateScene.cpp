#include "PlayOperateScene.h"
#include "SceneManager.h"
#include "Quad.h"
#include "Application.h"

void PlayOperateScene::Init()
{
	auto bg				= Object::Create<Quad>();			// �w�i
	auto keyPad			= Object::Create<Quad>();			// ������@
	auto close			= Object::Create<Quad>();			// ����A�C�R��
	auto frame			= Object::Create<Quad>();			// �A�C�R�����͂ރt���[��
	auto fade			= Object::Create<Quad>();			// �t�F�[�h�C���E�t�F�[�h�A�E�g�p

	bg->SetTex("asset/Texture/Bg.png");						// �摜�ǂݍ���
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);			// �傫����ݒ�
	bg->layer = -1;											// ���C���[��ݒ�

	keyPad->SetTex("asset/Texture/KeyPad.png");				// �摜�ǂݍ���
	keyPad->SetPos(0.0f, 100.0f, 0.0f);						// ���W��ݒ�
	keyPad->SetScale(1000.0f, 800.0f, 0.0f);				// �傫����ݒ�

	close->SetTex("asset/Texture/Close.png");				// �摜�ǂݍ���
	close->SetPos(0.0f, -400.0f, 0.0f);						// ���W��ݒ�
	close->SetScale(300.0f, 150.0f, 0.0f);					// �傫����ݒ�

	frame->SetTex("asset/Texture/Frame.png");				// �摜�ǂݍ���
	frame->SetPos(0.0f, -400.0f, 0.0f);						// ���W��ݒ�
	frame->SetScale(300.0f, 150.0f, 0.0f);					// �傫����ݒ�
	frame->tags.AddTag("frame");							// �^�O�t��

	// �t�F�[�h�C���E�t�F�[�h�A�E�g
	fade->SetTex("asset/Texture/Fade.png");						// �摜�ǂݍ���
	fade->SetPos(0.0f, 0.0f, 0.0f);								// ���W�ݒ�
	fade->SetScale(1920.0f, 1080.0f, 0.0f);						// �傫����ݒ�
	fade->tags.AddTag("Fade");									// �^�O�t��
	fade->layer = 10;											// ���C���[��ݒ�
}

void PlayOperateScene::Update()
{
	if (fade_In == true)
	{
		Fade_In();			// �t�F�[�h�C������		(���邭�Ȃ�)
	}
	
	Back_ToTitle();			// �^�C�g���ɖ߂�
	if (fadeOut_Start == true)
	{
		Fade_Out();			// �t�F�[�h�A�E�g����	(�Â��Ȃ�)
	}
	
	auto objects = objectInstance;
	for (auto& obj : objects)
	{
		obj->Update();
	}
}

// �^�C�g���ɖ߂�
void PlayOperateScene::Back_ToTitle()
{
	// �G���^�[�L�[orB�{�^��orA�{�^������������
	if (input.GetKeyTrigger(VK_RETURN) ||
		input.GetButtonTrigger(XINPUT_B) ||
		input.GetButtonTrigger(XINPUT_A))
	{
		fadeOut_Start = true;
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
	}
	// �Â��Ȃ肫��ƑJ�ڂ���
	if (fadeOut_End == true)
	{
		//���݂̃V�[�����uTitleScene�v�ɐ؂�ւ���
		SceneManager::ChangeScene(TITLE);
	}
}

// �t�F�[�h�C������		(���邭�Ȃ�)
void PlayOperateScene::Fade_In()
{
	if (Application::GetFpsCounter() % 6 == 0)
	{
		countFadeIn += 1;
		auto Fade = GetInstance()->GetObjects<Quad>();
		for (auto& fade : Fade)
		{
			if (fade->tags.SearchTag("Fade"))
			{
				switch (countFadeIn)
				{
				case 1: {
					fade->SetTex("asset/Texture/Fade/Fade_In_1.png");	// �摜�ǂݍ���
					break; }
				case 2: {
					fade->SetTex("asset/Texture/Fade/Fade_In_2.png");	// �摜�ǂݍ���
					break; }
				case 3: {
					fade->SetTex("asset/Texture/Fade/Fade_In_3.png");	// �摜�ǂݍ���
					break; }
				case 4: {
					fade->SetTex("asset/Texture/Fade/Fade_In_4.png");	// �摜�ǂݍ���
					break; }
				case 5: {
					fade->SetTex("asset/Texture/Fade/Fade_In_5.png");	// �摜�ǂݍ���
					break; }
				case 6: {
					fade->SetTex("asset/Texture/Fade/Fade_In_6.png");	// �摜�ǂݍ���
					break; }
				case 7: {
					fade->SetTex("asset/Texture/Fade/Fade_In_7.png");	// �摜�ǂݍ���
					break; }
				case 8: {
					fade->SetTex("asset/Texture/Fade/Fade_In_8.png");	// �摜�ǂݍ���
					break; }
				case 9: {
					fade->SetTex("asset/Texture/Fade/Fade_In_9.png");	// �摜�ǂݍ���
					break; }
				case 10: {
					fade->SetTex("asset/Texture/Fade/Fade_In_10.png");	// �摜�ǂݍ���
					break; }
				default: {
					fade->SetColor(1.0f, 1.0f, 1.0f, 0.0f);
					fade->SetTex("asset/Texture/Fade.png");		// �摜�ǂݍ���
					fade_In = false;							// �t�F�[�h�C���I��
					break; }
				}
			}
		}
	}
}

// �t�F�[�h�A�E�g����	(�Â��Ȃ�)
void PlayOperateScene::Fade_Out()
{
	if (Application::GetFpsCounter() % 6 == 0)
	{
		countFadeOut += 1;
		auto Fade = GetInstance()->GetObjects<Quad>();
		for (auto& fade : Fade)
		{
			if (fade->tags.SearchTag("Fade"))
			{
				fade->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
				switch (countFadeOut)
				{
				case 1: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_1.png");	// �摜�ǂݍ���
					break; }
				case 2: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_2.png");	// �摜�ǂݍ���
					break; }
				case 3: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_3.png");	// �摜�ǂݍ���
					break; }
				case 4: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_4.png");	// �摜�ǂݍ���
					break; }
				case 5: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_5.png");	// �摜�ǂݍ���
					break; }
				case 6: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_6.png");	// �摜�ǂݍ���
					break; }
				case 7: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_7.png");	// �摜�ǂݍ���
					break; }
				case 8: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_8.png");	// �摜�ǂݍ���
					break; }
				case 9: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_9.png");	// �摜�ǂݍ���
					break; }
				case 10: {
					fade->SetTex("asset/Texture/Fade/Fade_Out_10.png");	// �摜�ǂݍ���
					break; }
				default: {
					fade->SetTex("asset/Texture/Fade.png");		// �摜�ǂݍ���
					fadeOut_End = true;
					break; }
				}
			}
		}
	}
}