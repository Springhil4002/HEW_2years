#include "TitleScene.h"
#include "SceneManager.h"
#include "Quad.h"
#include "Application.h"

void TitleScene::Init()
{
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// �T�E���h��~
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// �T�E���h��~
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM005);	// �T�E���h��~
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM001);	// �T�E���h�Đ�
	
	// �I�u�W�F�N�g�쐬
	auto bg				= Object::Create<Quad>();			// �w�i
	auto titleLogo		= Object::Create<Quad>();			// �^�C�g�����S
	auto gameStart		= Object::Create<Quad>();			// �Q�[���X�^�[�g�̃A�C�R��
	auto playOperate	= Object::Create<Quad>();			// �V�ѕ��̃A�C�R��
	auto frame			= Object::Create<Quad>();			// �A�C�R�����͂ރt���[��
	// �t�F�[�h�C���E�t�F�[�h�A�E�g
	auto fade = Object::Create<Quad>();
	fade->SetTex("asset/Texture/Fade.png");						// �摜�ǂݍ���
	fade->SetPos(0.0f, 0.0f, 0.0f);								// ���W�ݒ�
	fade->SetScale(1920.0f, 1080.0f, 0.0f);						// �傫����ݒ�
	fade->tags.AddTag("Fade");									// �^�O�t��
	fade->layer = 10;											// ���C���[��ݒ�

	Quad* fade_move[20];
	for (int i = 0; i < 20; i++)
	{
		fade_move[i] = Object::Create<Quad>();
		fade_move[i]->layer = -10;
	}
	for (int i = 0; i < 20; i++)
	{
		switch (i)
		{
		case 0:
			fade_move[i]->SetTex("asset/Texture/Fade/Fade_In_1.png");		// �摜�ǂݍ���
			break;
		case 1:
			fade_move[i]->SetTex("asset/Texture/Fade/Fade_In_2.png");		// �摜�ǂݍ���
			break;
		case 2:
			fade_move[i]->SetTex("asset/Texture/Fade/Fade_In_3.png");		// �摜�ǂݍ���
			break;
		case 3:
			fade_move[3]->SetTex("asset/Texture/Fade/Fade_In_4.png");		// �摜�ǂݍ���
			break;
		case 4:
			fade_move[4]->SetTex("asset/Texture/Fade/Fade_In_5.png");		// �摜�ǂݍ���
			break;
		case 5:
			fade_move[5]->SetTex("asset/Texture/Fade/Fade_In_6.png");		// �摜�ǂݍ���
			break;
		case 6:
			fade_move[6]->SetTex("asset/Texture/Fade/Fade_In_7.png");		// �摜�ǂݍ���
			break;
		case 7:
			fade_move[7]->SetTex("asset/Texture/Fade/Fade_In_8.png");		// �摜�ǂݍ���
			break;
		case 8:
			fade_move[8]->SetTex("asset/Texture/Fade/Fade_In_9.png");		// �摜�ǂݍ���
			break;
		case 9:
			fade_move[9]->SetTex("asset/Texture/Fade/Fade_In_10.png");		// �摜�ǂݍ���
			break;
		case 10:
			fade_move[10]->SetTex("asset/Texture/Fade/Fade_Out_1.png");		// �摜�ǂݍ���
			break;
		case 11:
			fade_move[11]->SetTex("asset/Texture/Fade/Fade_Out_2.png");		// �摜�ǂݍ���
			break;
		case 12:
			fade_move[12]->SetTex("asset/Texture/Fade/Fade_Out_3.png");		// �摜�ǂݍ���
			break;
		case 13:
			fade_move[13]->SetTex("asset/Texture/Fade/Fade_Out_4.png");		// �摜�ǂݍ���
			break;
		case 14:
			fade_move[14]->SetTex("asset/Texture/Fade/Fade_Out_5.png");		// �摜�ǂݍ���
			break;
		case 15:
			fade_move[15]->SetTex("asset/Texture/Fade/Fade_Out_6.png");		// �摜�ǂݍ���
			break;
		case 16:
			fade_move[16]->SetTex("asset/Texture/Fade/Fade_Out_7.png");		// �摜�ǂݍ���
			break;
		case 17:
			fade_move[17]->SetTex("asset/Texture/Fade/Fade_Out_8.png");		// �摜�ǂݍ���
			break;
		case 18:
			fade_move[18]->SetTex("asset/Texture/Fade/Fade_Out_9.png");		// �摜�ǂݍ���	
			break;
		case 19:
			fade_move[19]->SetTex("asset/Texture/Fade/Fade_Out_10.png");	// �摜�ǂݍ���
			break;
		}
	}
				
	bg->SetTex("asset/Texture/Bg.png");						// �摜�ǂݍ���
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);			// �傫����ݒ�
	bg->layer = -1;											// ���C���[�ݒ�

	titleLogo->SetTex("asset/Texture/Title_Logo.png");		// �摜�ǂݍ���
	titleLogo->SetPos(0.0f, 200.0f, 0.0f);					// ���W��ݒ�
	titleLogo->SetScale(1200.0f, 600.0f, 0.0f);				// �傫����ݒ�

	gameStart->SetTex("asset/Texture/Start_Logo.png");		// �摜�ǂݍ���
	gameStart->SetPos(0.0f, -200.0f, 0.0f);					// ���W��ݒ�
	gameStart->SetScale(800.0f, 180.0f, 0.0f);				// �傫����ݒ�

	playOperate->SetTex("asset/Texture/How_to_play.png");	// �摜�ǂݍ���
	playOperate->SetPos(0.0f, -400.0f, 0.0f);				// ���W��ݒ�
	playOperate->SetScale(600.0f, 180.0f, 0.0f);			// �傫����ݒ�

	frame->SetTex("asset/Texture/Frame.png");				// �摜�ǂݍ���
	frame->SetPos(0.0f, -200.0f, 0.0f);						// ���W��ݒ�
	frame->SetScale(800.0f, 200.0f, 0.0f);					// �傫����ݒ�
	frame->tags.AddTag("frame");							// �^�O�t��

	fade_In = true;
}

void TitleScene::Update()
{
	if (fade_In == true)
	{
		Fade_In();		// �t�F�[�h�C������		(���邭�Ȃ�)
	}
	
	if (fadeOut_Start == true)
	{
		Fade_Out();	// �t�F�[�h�A�E�g����	(�Â��Ȃ�)
	}

	Frame_Input();	// �t���[���ړ����͏���
	Frame_Move();	// �t���[���̈ړ�����
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
				quad->SetPos(0.0f, -210.0f, 0.0f);				// ���W��ݒ�
				quad->SetScale(800.0f, 200.0f, 0.0f);			// �傫����ݒ�
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
				quad->SetScale(600.0f, 200.0f, 0.0f);			// �傫����ݒ�
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
void TitleScene::Fade_Out()
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