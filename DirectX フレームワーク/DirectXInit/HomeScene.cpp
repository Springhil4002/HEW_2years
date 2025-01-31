#include "HomeScene.h"
#include "SceneManager.h"
#include "Quad.h"
#include "Application.h"

// �R���X�g���N�^
HomeScene::HomeScene(int _num)
{
	Init(_num);
}

// ����������
void HomeScene::Init(int _num)
{
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM001);			// �T�E���h��~
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);			// �T�E���h��~
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM005);			// �T�E���h��~
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM002);			// �T�E���h�Đ�
	homeSceneNum = _num;
		
	// �X�e�[�W�I���V�[���̕`�敪�򏈗�
	switch (homeSceneNum) {
	case 1: {
		frameNum = 1;
		// �I�u�W�F�N�g�̍쐬
		auto bg						= Object::Create<Quad>();		// �w�i
		auto stage_Logo1			= Object::Create<Quad>();		// �X�e�[�W���S
		auto stage_Logo2			= Object::Create<Quad>();		// �X�e�[�W���S
		auto stage_Logo3			= Object::Create<Quad>();		// �X�e�[�W���S
		auto rightArrow				= Object::Create<Quad>();		// ���A�C�R��
		auto frame					= Object::Create<Quad>();		// �A�C�R���̘g
		auto backTitle				= Object::Create<Quad>();		// �^�C�g���ɖ߂�
		auto howToPlay1				= Object::Create<Quad>();		// �������	����
		auto howToPlay2				= Object::Create<Quad>();		// �������	LB
		auto howToPlay3				= Object::Create<Quad>();		// �������	RB
		auto howToPlay4				= Object::Create<Quad>();		// �������	�㉺
		auto howToPlay5				= Object::Create<Quad>();		// �������	���E

		bg->SetTex("asset/Texture/Bg.png");							// �摜�ǂݍ���
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);				// �傫����ݒ�
		bg->layer = -1;												// ���C���[��ݒ�

		// �t�F�[�h�C���I�u�W�F�N�g�쐬
		auto fade = Object::Create<Quad>();
		fade->SetTex("asset/Texture/Fade.png");		// �摜�ǂݍ���
		fade->SetPos(0.0f, 0.0f, 0.0f);				// ���W�ݒ�
		fade->SetScale(1920.0f, 1080.0f, 0.0f);		// �傫����ݒ�
		fade->tags.AddTag("Fade");					// �^�O�t��
		fade->layer = 10;							// ���C���[��ݒ�

		stage_Logo1->SetTex("asset/Texture/Stage1.png");			// �摜�ǂݍ���
		stage_Logo1->SetPos(300.0f, 300.0f, 0.0f);					// ���W��ݒ�
		stage_Logo1->SetScale(400.0f, 150.0f, 0.0f);				// �傫����ݒ�

		stage_Logo2->SetTex("asset/Texture/Stage2.png");			// �摜�ǂݍ���
		stage_Logo2->SetPos(400.0f, 0.0f, 0.0f);					// ���W��ݒ�
		stage_Logo2->SetScale(400.0f, 150.0f, 0.0f);				// �傫����ݒ�

		stage_Logo3->SetTex("asset/Texture/Stage3.png");			// �摜�ǂݍ���
		stage_Logo3->SetPos(300.0f, -300.0f, 0.0f);					// ���W��ݒ�
		stage_Logo3->SetScale(400.0f, 150.0f, 0.0f);				// �傫����ݒ�

		rightArrow->SetTex("asset/Texture/ToHome_2.png");			// �摜�ǂݍ���
		rightArrow->SetPos(800.0f, 0.0f, 0.0f);						// ���W��ݒ�
		rightArrow->SetScale(200.0f, 75.0f, 0.0f);					// �傫����ݒ�
			
		frame->SetTex("asset/Texture/Frame.png");					// �摜�ǂݍ���
		frame->SetPos(300.0f, 300.0f, 0.0f);						// ���W��ݒ�
		frame->SetScale(420.0f, 150.0f, 0.0f);						// �傫����ݒ�
		frame->tags.AddTag("frame");								// �^�O�t��

		backTitle->SetTex("asset/Texture/BackTitle.png");			// �摜�ǂݍ���
		backTitle->SetPos(-900.0f, 480.0f, 0.0f);					// ���W��ݒ�
		backTitle->SetScale(100.0f, 100.0f, 0.0f);					// �傫����ݒ�

		howToPlay1->SetTex("asset/Texture/Decision_Logo.png");		// �摜�ǂݍ���
		howToPlay1->SetPos(-400.0f, 300.0f, 0.0f);					// ���W�ݒ�
		howToPlay1->SetScale(400.0f, 150.0f, 0.0f);					// �傫����ݒ�

		howToPlay2->SetTex("asset/Texture/LB_Logo.png");			// �摜�ǂݍ���
		howToPlay2->SetPos(-400.0f, 150.0f,0.0f);					// ���W�ݒ�
		howToPlay2->SetScale(800.0f, 150.0f, 0.0f);					// �傫����ݒ�
		
		howToPlay3->SetTex("asset/Texture/RB_Logo.png");			// �摜�ǂݍ���
		howToPlay3->SetPos(-400.0f, 0.0f, 0.0f);					// ���W�ݒ�
		howToPlay3->SetScale(800.0f, 150.0f, 0.0f);					// �傫����ݒ�

		howToPlay4->SetTex("asset/Texture/LeftRight_Logo.png");		// �摜�ǂݍ���
		howToPlay4->SetPos(-400.0f, -150.0f, 0.0f);					// ���W�ݒ�
		howToPlay4->SetScale(600.0f, 150.0f, 0.0f);					// �傫����ݒ�

		howToPlay5->SetTex("asset/Texture/UpDown_Logo.png");		// �摜�ǂݍ���
		howToPlay5->SetPos(-400.0f, -300.0f, 0.0f);					// ���W�ݒ�
		howToPlay5->SetScale(600.0f, 150.0f, 0.0f);					// �傫����ݒ�

		break; }
	case 2: {
		frameNum = 4;		
		auto bg						= Object::Create<Quad>();		// �w�i
		auto stage_Logo4			= Object::Create<Quad>();		// �X�e�[�W���S
		auto stage_Logo5			= Object::Create<Quad>();		// �X�e�[�W���S
		auto stage_Logo6			= Object::Create<Quad>();		// �X�e�[�W���S
		auto stage_Logo7			= Object::Create<Quad>();		// �X�e�[�W���S
		auto stage_Logo8			= Object::Create<Quad>();		// �X�e�[�W���S
		auto leftArrow				= Object::Create<Quad>();		// ���A�C�R��
		auto frame					= Object::Create<Quad>();		// �A�C�R�����͂ރt���[��
		auto backTitle				= Object::Create<Quad>();		// �^�C�g���ɖ߂�

		bg->SetTex("asset/Texture/Bg.png");							// �摜�ǂݍ���
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);				// �傫����ݒ�
		bg->layer = -1;												// ���C���[��ݒ�

		// �t�F�[�h�C���E�t�F�[�h�A�E�g�p
		auto fade = Object::Create<Quad>();
		fade->SetTex("asset/Texture/Fade_Black.png",			// �摜�ǂݍ���
			1, 1, 0, 0, 1.0f, 1.0f, 1.0f, 1.0f);
		fade->SetPos(0.0f, 0.0f, 0.0f);							// ���W�ݒ�
		fade->SetScale(1920.0f, 1080.0f, 0.0f);					// �傫����ݒ�
		fade->tags.AddTag("Fade");								// �^�O�t��
		fade->layer = 2;										// ���C���[��ݒ�


		stage_Logo4->SetTex("asset/Texture/Stage4.png");			// �摜�ǂݍ���
		stage_Logo4->SetPos(-450.0f, 300.0f, 0.0f);					// ���W��ݒ�
		stage_Logo4->SetScale(400.0f, 150.0f, 0.0f);				// �傫����ݒ�

		stage_Logo5->SetTex("asset/Texture/Stage5.png");			// �摜�ǂݍ���
		stage_Logo5->SetPos(0.0f, 300.0f, 0.0f);					// ���W��ݒ�
		stage_Logo5->SetScale(400.0f, 150.0f, 0.0f);				// �傫����ݒ�

		stage_Logo6->SetTex("asset/Texture/Stage6.png");			// �摜�ǂݍ���
		stage_Logo6->SetPos(450.0f, 300.0f, 0.0f);					// ���W��ݒ�
		stage_Logo6->SetScale(400.0f, 150.0f, 0.0f);				// �傫����ݒ�

		stage_Logo7->SetTex("asset/Texture/Stage7.png");			// �摜�ǂݍ���
		stage_Logo7->SetPos(-300.0f, -300.0f, 0.0f);				// ���W��ݒ�
		stage_Logo7->SetScale(400.0f, 150.0f, 0.0f);				// �傫����ݒ�

		stage_Logo8->SetTex("asset/Texture/Stage8.png");			// �摜�ǂݍ���
		stage_Logo8->SetPos(300.0f, -300.0f, 0.0f);					// ���W��ݒ�
		stage_Logo8->SetScale(400.0f, 150.0f, 0.0f);				// �傫����ݒ�

		leftArrow->SetTex("asset/Texture/ToHome_1.png");			// �摜�ǂݍ���
		leftArrow->SetPos(-800.0f, 0.0f, 0.0f);						// ���W��ݒ�
		leftArrow->SetScale(200.0f, 75.0f, 0.0f);					// �傫����ݒ�

		frame->SetTex("asset/Texture/Frame.png");					// �摜�ǂݍ���
		frame->SetPos(-450.0f, 300.0f, 0.0f);						// ���W��ݒ�
		frame->SetScale(420.0f, 150.0f, 0.0f);						// �傫����ݒ�
		frame->tags.AddTag("frame");								// �^�O�t��

		backTitle->SetTex("asset/Texture/BackTitle.png");			// �摜�ǂݍ���
		backTitle->SetPos(-900.0f, 480.0f, 0.0f);					// ���W��ݒ�
		backTitle->SetScale(100.0f, 100.0f, 0.0f);					// �傫����ݒ�
		break; }
	default: {
		break; }
	}
}

// �X�V����
void HomeScene::Update()
{
	if (fade_In = true)
	{
		// �t�F�[�h�C������	(���邭�Ȃ�)
		Fade_In();
	}
	Frame_Input();	// frame�ړ����͏���
	Frame_Move();	// frame�ړ�����
	ChangeHome();	// HomeScene�؂�ւ�����

	// �t�F�[�h�A�E�g����	(�Â��Ȃ�)
	if (fadeOut_Start == true)
	{
		Fade_Out();	
	}

	auto objects = objectInstance;
	for (auto& obj : objects)
	{
		obj->Update();
	}
}

// �t���[���ړ����͏���
void HomeScene::Frame_Input()
{
	if (GetHomeSceneNum() == 1)
	{
		/* �R���g���[���[:�\�����L�[
		*  �L�[�{�[�h   :�����L�[
		*  �ǂ��炩�������ꂽ��
		*/
		if ((input.GetButtonTrigger(XINPUT_DOWN) ||
			input.GetKeyTrigger(VK_DOWN)) &&
			GetFrameNum() < 3) {
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE003);	// �I����
			SetFrameNum(GetFrameNum() + 1);
		}
		/* �R���g���[���[:�\����L�[
		*  �L�[�{�[�h   :�����L�[
		*  �ǂ��炩�������ꂽ��
		*/
		if ((input.GetButtonTrigger(XINPUT_UP) ||
			input.GetKeyTrigger(VK_UP)) &&
			GetFrameNum() > 0) {
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE003);	// �I����
			SetFrameNum(GetFrameNum() - 1);
		}
	}
	if (GetHomeSceneNum() == 2)
	{
		/* �R���g���[���[:�\���E�L�[
		*  �L�[�{�[�h   :�����L�[
		*  �ǂ��炩�������ꂽ��
		*/
		if ((input.GetButtonTrigger(XINPUT_RIGHT) ||
			input.GetKeyTrigger(VK_RIGHT)) &&
			GetFrameNum() < 8) {
			if (GetFrameNum() == 0) {
				SceneManager::m_SoundManager.Play(SOUND_LABEL_SE003);	// �I����
				SetFrameNum(GetFrameNum() + 4);
			}
			else {
				SceneManager::m_SoundManager.Play(SOUND_LABEL_SE003);	// �I����
				SetFrameNum(GetFrameNum() + 1);
			}
		}
		/* �R���g���[���[:�\�����L�[
		*  �L�[�{�[�h   :�����L�[
		*  �ǂ��炩�������ꂽ��
		*/
		if ((input.GetButtonTrigger(XINPUT_LEFT) ||
			input.GetKeyTrigger(VK_LEFT)) &&
			GetFrameNum() >= 4) {
			if (GetFrameNum() == 4) {
				SceneManager::m_SoundManager.Play(SOUND_LABEL_SE003);	// �I����
				SetFrameNum(GetFrameNum() - 4);
			}
			else {
				SceneManager::m_SoundManager.Play(SOUND_LABEL_SE003);	// �I����
				SetFrameNum(GetFrameNum() - 1);
			}
		}
	}
}

// �t���[���ړ�����
void HomeScene::Frame_Move()
{
	// �t���[���A�C�R���̈ړ�����
	switch (GetFrameNum())
	{
	case 0: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(-900.0f, 480.0f, 0.0f);		// ���W��ݒ�
				quad->SetScale(100.0f, 130.0f, 0.0f);		// �傫����ݒ�
			}
		}
		// �G���^�[�L�[orB�{�^������������
		if (input.GetButtonTrigger(XINPUT_A) ||
			input.GetKeyTrigger(VK_RETURN))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// ���艹
		}
		if (fadeOut_End == true)
		{
			//���݂̃V�[�����uTitleScene�v�ɐ؂�ւ���
			SceneManager::ChangeScene(TITLE);
		}
		break; }
	case 1: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(300.0f, 300.0f, 0.0f);			// ���W��ݒ�
				quad->SetScale(420.0f, 150.0f, 0.0f);		// �傫����ݒ�
			}
		}
		// �G���^�[�L�[orB�{�^������������
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// ���艹
		}
		if (fadeOut_End == true)
		{
			//���݂̃V�[�����uGameScene�v�ɐ؂�ւ���
			SceneManager::ChangeScene(GAME_1, 1);
		}
		break; }
	case 2: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(400.0f, 0.0f, 0.0f);			// ���W��ݒ�
				quad->SetScale(420.0f, 150.0f, 0.0f);		// �傫����ݒ�
			}
		}
		// �G���^�[�L�[orB�{�^������������
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// ���艹
		}
		if (fadeOut_End == true)
		{
			//���݂̃V�[�����uGameScene�v�ɐ؂�ւ���
			SceneManager::ChangeScene(GAME_2, 2);
		}
		break; }
	case 3: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(300.0f, -300.0f, 0.0f);		// ���W��ݒ�
				quad->SetScale(420.0f, 150.0f, 0.0f);		// �傫����ݒ�
			}
		}
		// �G���^�[�L�[orB�{�^������������
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// ���艹
		}
		if (fadeOut_End == true)
		{
			//���݂̃V�[�����uGameScene�v�ɐ؂�ւ���
			SceneManager::ChangeScene(GAME_3, 3);
		}
		break; }
	case 4: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(-450.0f, 300.0f, 0.0f);		// ���W��ݒ�
				quad->SetScale(420.0f, 150.0f, 0.0f);		// �傫����ݒ�
			}
		}
		// �G���^�[�L�[orB�{�^������������
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// ���艹
		}
		if (fadeOut_End == true)
		{
			//���݂̃V�[�����uGameScene�v�ɐ؂�ւ���
			SceneManager::ChangeScene(GAME_4, 4);
		}
		break; }
	case 5: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(0.0f, 300.0f, 0.0f);			// ���W��ݒ�
				quad->SetScale(420.0f, 150.0f, 0.0f);		// �傫����ݒ�
			}
		}
		// �G���^�[�L�[orB�{�^������������
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// ���艹
		}
		if (fadeOut_End == true)
		{
			//���݂̃V�[�����uGameScene�v�ɐ؂�ւ���
			SceneManager::ChangeScene(GAME_5, 5);
		}
		break; }
	case 6: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(450.0f, 300.0f, 0.0f);			// ���W��ݒ�
				quad->SetScale(420.0f, 150.0f, 0.0f);		// �傫����ݒ�
			}
		}
		// �G���^�[�L�[orB�{�^������������
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// ���艹
			
		}
		if (fadeOut_End == true)
		{
			//���݂̃V�[�����uGameScene�v�ɐ؂�ւ���
			SceneManager::ChangeScene(GAME_6, 6);
		}
		break; }
	case 7: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(-300.0f, -300.0f, 0.0f);		// ���W��ݒ�
				quad->SetScale(420.0f, 150.0f, 0.0f);		// �傫����ݒ�
			}
		}
		// �G���^�[�L�[orB�{�^������������
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// ���艹
		}
		if (fadeOut_End == true)
		{
			//���݂̃V�[�����uGameScene�v�ɐ؂�ւ���
			SceneManager::ChangeScene(GAME_7, 7);
		}
		break; }
	case 8: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(300.0f, -300.0f, 0.0f);		// ���W��ݒ�
				quad->SetScale(420.0f, 150.0f, 0.0f);		// �傫����ݒ�
			}
		}
		// �G���^�[�L�[orB�{�^������������
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			fadeOut_Start = true;
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// ���艹
		}
		if (fadeOut_End == true)
		{
			//���݂̃V�[�����uGameScene�v�ɐ؂�ւ���
			SceneManager::ChangeScene(GAME_8, 8);
		}
		break; }
	default:
		break;
	}
}

// HomwScene�؂�ւ�����
void HomeScene::ChangeHome()
{
	/*�R���g���[���[:RB�{�^��
	 *�L�[�{�[�h   :2�L�[
	 * �ǂ��炩�������ꂽ��
	 */
	if (input.GetButtonTrigger(XINPUT_RIGHT_SHOULDER) ||
		input.GetKeyTrigger	  (VK_2))
	{
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// ���艹
		//���݂̃V�[�����uHomeScene(2����)�v�ɐ؂�ւ���
		SceneManager::ChangeScene(HOME_2,2);
	}

	/*�R���g���[���[:LB�{�^��
	 *�L�[�{�[�h   :1�L�[
	 * �ǂ��炩�������ꂽ��
	 */
	if (input.GetButtonTrigger(XINPUT_LEFT_SHOULDER) ||
		input.GetKeyTrigger	  (VK_1))
	{
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// ���艹
		//���݂̃V�[�����uHomeScene(1����)�v�ɐ؂�ւ���
		SceneManager::ChangeScene(HOME_1,1);
	}
}

// �t�F�[�h�C������		(���邭�Ȃ�)
void HomeScene::Fade_In()
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
					fade->SetTex("asset/Texture/Fade_In_1.png");	// �摜�ǂݍ���
					break; }
				case 2: {
					fade->SetTex("asset/Texture/Fade_In_2.png");	// �摜�ǂݍ���
					break; }
				case 3: {
					fade->SetTex("asset/Texture/Fade_In_3.png");	// �摜�ǂݍ���
					break; }
				case 4: {
					fade->SetTex("asset/Texture/Fade_In_4.png");	// �摜�ǂݍ���
					break; }
				case 5: {
					fade->SetTex("asset/Texture/Fade_In_5.png");	// �摜�ǂݍ���
					break; }
				case 6: {
					fade->SetTex("asset/Texture/Fade_In_6.png");	// �摜�ǂݍ���
					break; }
				case 7: {
					fade->SetTex("asset/Texture/Fade_In_7.png");	// �摜�ǂݍ���
					break; }
				case 8: {
					fade->SetTex("asset/Texture/Fade_In_8.png");	// �摜�ǂݍ���
					break; }
				case 9: {
					fade->SetTex("asset/Texture/Fade_In_9.png");	// �摜�ǂݍ���
					break; }
				case 10: {
					fade->SetTex("asset/Texture/Fade_In_10.png");	// �摜�ǂݍ���
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

// �t�F�[�h�A�E�g����	(�Â��Ȃ�)
void HomeScene::Fade_Out()
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
				fade->SetTex("asset/Texture/Fade_Out_1.png");	// �摜�ǂݍ���
				break; }
			case 2: {
				fade->SetTex("asset/Texture/Fade_Out_2.png");	// �摜�ǂݍ���
				break; }
			case 3: {
				fade->SetTex("asset/Texture/Fade_Out_3.png");	// �摜�ǂݍ���
				break; }
			case 4: {
				fade->SetTex("asset/Texture/Fade_Out_4.png");	// �摜�ǂݍ���
				break; }
			case 5: {
				fade->SetTex("asset/Texture/Fade_Out_5.png");	// �摜�ǂݍ���
				break; }
			case 6: {
				fade->SetTex("asset/Texture/Fade_Out_6.png");	// �摜�ǂݍ���
				break; }
			case 7: {
				fade->SetTex("asset/Texture/Fade_Out_7.png");	// �摜�ǂݍ���
				break; }
			case 8: {
				fade->SetTex("asset/Texture/Fade_Out_8.png");	// �摜�ǂݍ���
				break; }
			case 9: {
				fade->SetTex("asset/Texture/Fade_Out_9.png");	// �摜�ǂݍ���
				break; }
			case 10: {
				fade->SetTex("asset/Texture/Fade_Out_10.png");	// �摜�ǂݍ���
				break; }
			default: {
				fade->SetColor(1.0f, 1.0f, 1.0f, 0.0f);
				fade->SetTex("asset/Texture/Fade.png");		// �摜�ǂݍ���
				fadeOut_End = true;
				break; }
			}
		}
	}
}