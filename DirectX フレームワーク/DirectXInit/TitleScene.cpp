#include "TitleScene.h"
#include "SceneManager.h"
#include "Quad.h"

void TitleScene::Init()
{
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// �T�E���h��~
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM005);	// �T�E���h��~
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM001);	// �T�E���h�Đ�
	
	// �I�u�W�F�N�g�쐬
	auto bg				= Object::Create<Quad>();			// �w�i
	auto titleLogo		= Object::Create<Quad>();			// �^�C�g�����S
	auto gameStart		= Object::Create<Quad>();			// �Q�[���X�^�[�g�̃A�C�R��
	auto playOperate	= Object::Create<Quad>();			// �V�ѕ��̃A�C�R��
	auto frame			= Object::Create<Quad>();			// �A�C�R�����͂ރt���[��
	auto fade			= Object::Create<Quad>();			// �t�F�[�h�C���E�t�F�[�h�A�E�g�p
				
	bg->SetTex("asset/Texture/Title_bg.jpg");				// �摜�ǂݍ���
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);			// �傫����ݒ�
	bg->layer = -1;											// ���C���[�ݒ�

	titleLogo->SetTex("asset/Texture/Title_Logo.jpg");		// �摜�ǂݍ���
	titleLogo->SetPos(0.0f, 200.0f, 0.0f);					// ���W��ݒ�
	titleLogo->SetScale(1000.0f, 600.0f, 0.0f);				// �傫����ݒ�

	gameStart->SetTex("asset/Texture/Start_Logo.png");		// �摜�ǂݍ���
	gameStart->SetPos(0.0f, -200.0f, 0.0f);					// ���W��ݒ�
	gameStart->SetScale(600.0f, 200.0f, 0.0f);				// �傫����ݒ�

	playOperate->SetTex("asset/Texture/How_to_play.png");	// �摜�ǂݍ���
	playOperate->SetPos(0.0f, -400.0f, 0.0f);				// ���W��ݒ�
	playOperate->SetScale(400.0f, 150.0f, 0.0f);			// �傫����ݒ�

	frame->SetTex("asset/Texture/Frame.png");				// �摜�ǂݍ���
	frame->SetPos(0.0f, -200.0f, 0.0f);						// ���W��ݒ�
	frame->SetScale(600.0f, 200.0f, 0.0f);					// �傫����ݒ�
	frame->tags.AddTag("frame");							// �^�O�t��

	fade->SetTex("asset/Texture/Fade_Black.png",			// �摜�ǂݍ���
			1,1,0,0,	1.0f,1.0f,1.0f,1.0f);								
	fade->SetPos(0.0f, 0.0f, 0.0f);							// ���W�ݒ�
	fade->SetScale(1920.0f, 1080.0f, 0.0f);					// �傫����ݒ�
	fade->tags.AddTag("Fade");								// �^�O�t��
	fade->layer = 2;										// ���C���[��ݒ�
}

void TitleScene::Update()
{
	Fade_In();		// �t�F�[�h�C������		(���邭�Ȃ�)
	
	Frame_Input();	// �t���[���ړ����͏���
	Frame_Move();	// �t���[���̈ړ�����
	if (fadeOut_Start == true)
	{
		Fade_Out();	// �t�F�[�h�A�E�g����	(�Â��Ȃ�)
	}

	auto objects = objectInstance;
	for (auto& obj : objects)
	{
		obj->Update();
	}
}

// �t���[���ړ����͏���
void TitleScene::Frame_Input()
{
	/* �R���g���[���[ :�\�����L�[
	 *  �L�[�{�[�h   :�����L�[
	 *  �ǂ��炩�������ꂽ��
	 */
	if((input.GetButtonTrigger(XINPUT_DOWN) ||
		input.GetKeyTrigger	  (VK_DOWN)) &&
		GetFrameNum() < 2) {
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE003);	// �I����
		SetFrameNum(GetFrameNum() + 1);
	}
	/* �R���g���[���[ :�\����L�[
	 *  �L�[�{�[�h   :�����L�[
	 *  �ǂ��炩�������ꂽ��
	 */
	if((input.GetButtonTrigger(XINPUT_UP) ||
		input.GetKeyTrigger	  (VK_UP)) &&
		GetFrameNum() > 1) {
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE003);	// �I����
		SetFrameNum(GetFrameNum() - 1);
	}
}

// �t���[���̈ړ�����
void TitleScene::Frame_Move()
{
	switch (GetFrameNum())
	{
	case 1: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(0.0f, -200.0f, 0.0f);				// ���W��ݒ�
				quad->SetScale(600.0f, 200.0f, 0.0f);			// �傫����ݒ�
			}
		}
		// �G���^�[�L�[orB�{�^������������
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE001);	// ���艹
		}
		// �Â��Ȃ肫��ƑJ�ڂ���
		if (fadeOut_End == true)
		{
			//���݂̃V�[�����uHomeScene�v�ɐ؂�ւ���
			SceneManager::ChangeScene(HOME_1, 1);
		}
		break; }
	case 2: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(0.0f, -400.0f, 0.0f);				// ���W��ݒ�
				quad->SetScale(400.0f, 150.0f, 0.0f);			// �傫����ݒ�
			}
		}
		// �G���^�[�L�[orB�{�^������������
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// ���艹
		}
		// �Â��Ȃ肫��ƑJ�ڂ���
		if (fadeOut_End == true)
		{
			//���݂̃V�[�����uPlayOperateScene�v�ɐ؂�ւ���
			SceneManager::ChangeScene(PLAYOPERATE);
		}
		break; }
	default:
		break;
	}
}

// �t�F�[�h�C������		(���邭�Ȃ�)
void TitleScene::Fade_In()
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
void TitleScene::Fade_Out()
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