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
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// �T�E���h��~
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM005);	// �T�E���h��~
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM001);	// �T�E���h�Đ�
	
	// �I�u�W�F�N�g�쐬
	auto bg = Object::Create<Quad>();						
	auto titleLogo = Object::Create<Quad>();
	auto startLogo = Object::Create<Quad>();
	auto playLogo = Object::Create<Quad>();
	auto frame = Object::Create<Quad>();
				
	bg->SetTex("asset/Texture/Future.jpg");					// �摜�ǂݍ���
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);			// �傫����ݒ�
	bg->layer = -1;											// ���C���[�ݒ�

	titleLogo->SetTex("asset/Texture/Title_Logo.png");		// �摜�ǂݍ���
	titleLogo->SetPos(0.0f, 200.0f, 0.0f);					// ���W��ݒ�
	titleLogo->SetScale(800.0f, 350.0f, 0.0f);				// �傫����ݒ�

	startLogo->SetTex("asset/Texture/Start_Logo.png");		// �摜�ǂݍ���
	startLogo->SetPos(0.0f, -200.0f, 0.0f);					// ���W��ݒ�
	startLogo->SetScale(600.0f, 200.0f, 0.0f);				// �傫����ݒ�

	playLogo->SetTex("asset/Texture/How_to_play.png");		// �摜�ǂݍ���
	playLogo->SetPos(0.0f, -400.0f, 0.0f);					// ���W��ݒ�
	playLogo->SetScale(400.0f, 150.0f, 0.0f);				// �傫����ݒ�

	frame->SetTex("asset/Texture/Frame.png");				// �摜�ǂݍ���
	frame->SetPos(0.0f, -200.0f, 0.0f);						// ���W��ݒ�
	frame->SetScale(600.0f, 200.0f, 0.0f);					// �傫����ݒ�
	frame->tags.AddTag("frame");							// �^�O�t��
}

void TitleScene::Update()
{
	if ((input.GetButtonTrigger(XINPUT_DOWN) ||
		input.GetButtonTrigger(XINPUT_RIGHT) ||
		input.GetKeyTrigger(VK_S) ||
		input.GetKeyTrigger(VK_D)) &&
		frameNum < 2) {
		frameNum += 1;
	}
	if ((input.GetButtonTrigger(XINPUT_UP) ||
		input.GetButtonTrigger(XINPUT_LEFT) ||
		input.GetKeyTrigger(VK_W) ||
		input.GetKeyTrigger(VK_A)) &&
		frameNum > 1) {
		frameNum -= 1;
	}

	switch (frameNum)
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
			input.GetButtonTrigger(XINPUT_B))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
			//���݂̃V�[�����uHomeScene�v�ɐ؂�ւ���
			SceneManager::ChangeScene(HOME_1);
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
		
		break; }
	default:
		break;
	}
}

//void TitleScene::Draw()
//{
//	bg.Draw();		// �w�i��`��
//}