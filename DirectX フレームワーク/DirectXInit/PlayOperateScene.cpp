#include "PlayOperateScene.h"
#include "SceneManager.h"
#include "Quad.h"

void PlayOperateScene::Init()
{
	auto bg				= Object::Create<Quad>();			// �w�i
	auto keyPad			= Object::Create<Quad>();			// ������@
	auto close			= Object::Create<Quad>();			// ����A�C�R��
	auto frame			= Object::Create<Quad>();			// �A�C�R�����͂ރt���[��

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
}

void PlayOperateScene::Update()
{
	// �G���^�[�L�[orB�{�^������������
	if (input.GetKeyTrigger(VK_RETURN) ||
		input.GetButtonTrigger(XINPUT_B))
	{
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
		//���݂̃V�[�����uTitleScene�v�ɐ؂�ւ���
		SceneManager::ChangeScene(TITLE);
	}
}
