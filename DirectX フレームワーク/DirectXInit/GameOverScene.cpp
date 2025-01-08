#include "GameOverScene.h"
#include "SceneManager.h"
#include "Quad.h"

// �R���X�g���N�^(����������)
GameOverScene::GameOverScene()
{

}

// �f�X�g���N�^	(�������)
GameOverScene::~GameOverScene()
{

}

// ����������
void GameOverScene::Init()
{
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// �T�E���h���~
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM005);	// �T�E���h���Đ�
	auto bg = Object::Create<Quad>();
	auto logo = Object::Create<Quad>();
	auto returnTitle = Object::Create<Quad>();
	auto returnHome = Object::Create<Quad>();
	auto frame = Object::Create<Quad>();

	bg->SetTex("asset/Texture/GameOver_bg.png");
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
	bg->layer = -1;

	logo->SetTex("asset/Texture/GameOver.png");
	logo->SetPos(0.0f, 300.0f, 0.0f);
	logo->SetScale(600.0f, 400.0f, 0.0f);

	returnTitle->SetTex("asset/Texture/Return_toTitle.png");
	returnTitle->SetPos(-300.0f, -300.0f, 0.0f);
	returnTitle->SetScale(420.0f, 150.0f, 0.0f);

	returnHome->SetTex("asset/Texture/Return_toHome.png");
	returnHome->SetPos(300.0f, -300.0f, 0.0f);
	returnHome->SetScale(420.0f, 150.0f, 0.0f);

	frame->SetTex("asset/Texture/Frame.png");
	frame->SetPos(-300.0f, 300.0f, 0.0f);
	frame->SetScale(420.0f, 150.0f, 0.0f);
	frame->tags.AddTag("frame");
}
// �X�V����
void GameOverScene::Update()
{
	if (input.GetKeyTrigger(VK_D) ||
		input.GetKeyTrigger(VK_A) ||
		input.GetButtonTrigger(XINPUT_RIGHT) ||
		input.GetButtonTrigger(XINPUT_LEFT))
	{
		if((input.GetButtonTrigger(XINPUT_RIGHT) ||
			input.GetKeyTrigger(VK_D)) &&
			frameNum < 2) {
			frameNum += 1;
		}
		if ((input.GetButtonTrigger(XINPUT_LEFT) ||
			input.GetKeyTrigger(VK_A)) &&
			frameNum > 1) {
			frameNum -= 1;
		}
	}

	switch (frameNum)
	{
	case 1: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(-300.0f, -300.0f, 0.0f);
			}
		}

		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_B))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE001);
			//���݂̃V�[�����uTitleScene�v�ɐ؂�ւ���
			SceneManager::ChangeScene(SceneManager::TITLE);
		}
		break; }
	case 2: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(300.0f, -300.0f, 0.0f);
			}
		}

		if (input.GetKeyTrigger(VK_RETURN) ||
			input.GetButtonTrigger(XINPUT_B))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE001);
			//���݂̃V�[�����uGameScene�v�ɐ؂�ւ���
			SceneManager::ChangeScene(SceneManager::HOME_1);
		}
		break; }
	default:
		break;
	}
}