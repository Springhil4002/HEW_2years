#include "GameOverScene.h"
#include "SceneManager.h"
#include "Quad.h"

SCENE GameOverScene::isEndSceneNum = GAME_1;

// ����������
void GameOverScene::Init()
{
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM003);		// �T�E���h���~
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM004);		// �T�E���h���Đ�

	// �I�u�W�F�N�g�̍쐬
	auto bg							= Object::Create<Quad>();	// �w�i
	auto logo						= Object::Create<Quad>();	// �Q�[���I�[�o�[���S
	auto returnTitle				= Object::Create<Quad>();	//�u�^�C�g���ɖ߂�v�A�C�R��
	auto returnHome					= Object::Create<Quad>();	//�u�X�e�[�W�I���ɖ߂�v�A�C�R��
	auto retryLogo					= Object::Create<Quad>();	//�u���g���C�v�A�C�R��
	auto frame						= Object::Create<Quad>();	// �A�C�R�����͂ރt���[��

	bg->SetTex("asset/Texture/GameOver_bg.png");				// �摜�ǂݍ���
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);				// �傫����ݒ�
	bg->layer = -1;												// ���C���[��ݒ�

	logo->SetTex("asset/Texture/GameOver.png");					// �摜�ǂݍ���
	logo->SetPos(0.0f, 300.0f, 0.0f);							// ���W��ݒ�
	logo->SetScale(600.0f, 400.0f, 0.0f);						// �傫����ݒ�

	returnTitle->SetTex("asset/Texture/Return_toTitle.png");	// �摜�ǂݍ���
	returnTitle->SetPos(-450.0f, -300.0f, 0.0f);				// ���W��ݒ�
	returnTitle->SetScale(420.0f, 150.0f, 0.0f);				// �傫����ݒ�

	returnHome->SetTex("asset/Texture/Return_toHome.png");		// �摜�ǂݍ���
	returnHome->SetPos(0.0f, -300.0f, 0.0f);					// ���W��ݒ�
	returnHome->SetScale(420.0f, 150.0f, 0.0f);					// �傫����ݒ�

	retryLogo->SetTex("asset/Texture/Retry.png");				// �摜�ǂݍ���
	retryLogo->SetPos(450.0f, -300.0f, 0.0f);					// ���W��ݒ�
	retryLogo->SetScale(420.0f, 150.0f, 0.0f);					// �傫����ݒ�

	frame->SetTex("asset/Texture/Frame.png");					// �摜�ǂݍ���
	frame->SetPos(-450.0f, -300.0f, 0.0f);						// ���W��ݒ�
	frame->SetScale(420.0f, 150.0f, 0.0f);						// �傫����ݒ�
	frame->tags.AddTag("frame");								// �^�O�t��
}
// �X�V����
void GameOverScene::Update()
{
	Frame_Input();		// �t���[���ړ����͏���
	Frame_Move();		// �t���[���ړ�����
}

// �t���[���ړ����͏���
void GameOverScene::Frame_Input()
{
	/*�R���g���[���[:�\���E�L�[
	 *�L�[�{�[�h�@�@:�����L�[
	 *�ǂ��炩�������ꂽ��
	 */
	if ((input.GetButtonTrigger(XINPUT_RIGHT) ||
		input.GetKeyTrigger(VK_RIGHT)) &&
		GetFrameNum() < 3) {
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE003);	// �I����
		SetFrameNum(GetFrameNum() + 1);
	}
	/*�R���g���[���[:�\�����L�[
	 *�L�[�{�[�h�@�@:�����L�[
	 *�ǂ��炩�������ꂽ��
	 */
	if ((input.GetButtonTrigger(XINPUT_LEFT) ||
		input.GetKeyTrigger(VK_LEFT)) &&
		GetFrameNum() > 1) {
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE003);	// �I����
		SetFrameNum(GetFrameNum() - 1);
	}
}

// �t���[���ړ�����
void GameOverScene::Frame_Move()
{
	// �t���[���ړ������E���͌�̊e�V�[���J�ڏ���
	switch (GetFrameNum())
	{
	case 1: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(-450.0f, -300.0f, 0.0f);
			}
		}
		// �G���^�[�L�[orB�{�^������������
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// ���艹
			//���݂̃V�[�����uTitleScene�v�ɐ؂�ւ���
			SceneManager::ChangeScene(TITLE);
		}
		break; }
	case 2: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(0.0f, -300.0f, 0.0f);
			}
		}
		// �G���^�[�L�[orB�{�^������������
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// ���艹
			//���݂̃V�[�����uGameScene�v�ɐ؂�ւ���
			SceneManager::ChangeScene(HOME_1,1);
		}
		break; }
	case 3: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(450.0f, -300.0f, 0.0f);
			}
		}
		// �G���^�[�L�[orB�{�^������������
		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_A))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);	// ���艹
			int stageNum = (int)(GameOverScene::isEndSceneNum - SCENE_ENUM_OFFSET);
			//���݂̃V�[���𒼑O�ɃQ�[���I�[�o�[�����uGameScene�v�ɐ؂�ւ���
			SceneManager::ChangeScene(isEndSceneNum,stageNum);
		}
		break; }
	default:
		break;
	}
}