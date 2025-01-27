#include "PlayOperateScene.h"
#include "SceneManager.h"
#include "Quad.h"

void PlayOperateScene::Init()
{
	auto bg				= Object::Create<Quad>();			// �w�i
	auto keyPad			= Object::Create<Quad>();			// ������@
	auto close			= Object::Create<Quad>();			// ����A�C�R��
	auto frame			= Object::Create<Quad>();			// �A�C�R�����͂ރt���[��
	auto fade			= Object::Create<Quad>();			// �t�F�[�h�C���E�t�F�[�h�A�E�g�p

	bg->SetTex("asset/Texture/PlayOperate_bg.jpg");			// �摜�ǂݍ���
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);			// �傫����ݒ�
	bg->layer = -1;											// ���C���[��ݒ�

	keyPad->SetTex("asset/Texture/KeyPad.png");				// �摜�ǂݍ���
	keyPad->SetPos(0.0f, 100.0f, 0.0f);						// ���W��ݒ�
	keyPad->SetScale(1000.0f, 800.0f, 0.0f);				// �傫����ݒ�

	close->SetTex("asset/Texture/Close.png");				// �摜�ǂݍ���
	close->SetPos(0.0f, -400.0f, 0.0f);						// ���W��ݒ�
	close->SetScale(200.0f, 100.0f, 0.0f);					// �傫����ݒ�

	frame->SetTex("asset/Texture/Frame.png");				// �摜�ǂݍ���
	frame->SetPos(0.0f, -400.0f, 0.0f);						// ���W��ݒ�
	frame->SetScale(200.0f, 100.0f, 0.0f);					// �傫����ݒ�
	frame->tags.AddTag("frame");							// �^�O�t��

	fade->SetTex("asset/Texture/Fade_Black.png",			// �摜�ǂݍ���
		1, 1, 0, 0, 1.0f, 1.0f, 1.0f, 1.0f);
	fade->SetPos(0.0f, 0.0f, 0.0f);							// ���W�ݒ�
	fade->SetScale(1920.0f, 1080.0f, 0.0f);					// �傫����ݒ�
	fade->tags.AddTag("Fade");								// �^�O�t��
	fade->layer = 2;										// ���C���[��ݒ�
}

void PlayOperateScene::Update()
{
	Fade_In();				// �t�F�[�h�C������		(���邭�Ȃ�)

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
	auto Fade = GetInstance()->GetObjects<Quad>();
	for (auto& fade : Fade)
	{
		if (fade->tags.SearchTag("Fade"))
		{
			if (fade->GetColor().w >= 0.0f)
			{
				fade->SetColor(1.0f, 1.0f, 1.0f, fade->GetColor().w - 0.01f);
			}
		}
	}
}

// �t�F�[�h�A�E�g����	(�Â��Ȃ�)
void PlayOperateScene::Fade_Out()
{
	auto Fade = GetInstance()->GetObjects<Quad>();
	for (auto& fade : Fade)
	{
		if (fade->tags.SearchTag("Fade"))
		{
			if (fade->GetColor().w <= 1.0f)
			{
				fade->SetColor(1.0f, 1.0f, 1.0f, fade->GetColor().w + 0.05f);
			}
			else
			{
				fadeOut_End = true;
			}
		}
	}
}