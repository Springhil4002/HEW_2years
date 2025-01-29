#include "ResultScene.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "Quad.h"
#include "Ground.h"
#include "Player.h"
#include "Band.h"
#include "CoinNum.h"
#include "StarTip.h"

#include "iostream"

int ResultScene::tipCount = 0;
int ResultScene::meterCount = 0;

// ����������
void ResultScene::Init(int _num)
{
	tipCount = _num;										// �R�C���l������ݒ�
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM003);	// �T�E���h���~
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM005);	// �T�E���h���Đ�

	// �w�i�I�u�W�F�N�g�̍쐬
	auto bg = Object::Create<Quad>();
	bg->SetTex("asset/Texture/Night_Loom.jpg");
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
	bg->layer = -1;

	// �t�F�[�h�C���E�t�F�[�h�A�E�g�p
	auto fade = Object::Create<Quad>();
	fade->SetTex("asset/Texture/Fade_Black.png",			// �摜�ǂݍ���
		1, 1, 0, 0, 1.0f, 1.0f, 1.0f, 1.0f);
	fade->SetPos(0.0f, 0.0f, 0.0f);							// ���W�ݒ�
	fade->SetScale(1920.0f, 1080.0f, 0.0f);					// �傫����ݒ�
	fade->tags.AddTag("Fade");								// �^�O�t��
	fade->layer = 10;										// ���C���[��ݒ�

	// �v���C���[�I�u�W�F�N�g�̍쐬
	auto player = Object::Create<Player>();
	player->SetPos(-800.0f, -400.0f, 0.0f);

	// CLEAR�̃��S�I�u�W�F�N�g�̍쐬
	auto clear_Logo = Object::Create<Quad>();
	clear_Logo->SetTex("asset/Texture/Clear_Logo.png");
	clear_Logo->SetPos(0.0f, 0.0f, 0.0f);
	clear_Logo->SetScale(0.0f, 0.0f, 0.0f);
	clear_Logo->tags.AddTag("CLEAR");
	clear_Logo->layer = 1;

	// �n�ʃI�u�W�F�N�g�̍쐬
	Ground* ground[SET_BLOCK];
	for(int i = 0; i < SET_BLOCK; i++)
	{
		ground[i] = Object::Create<Ground>();
		ground[i]->SetPos(930.0f - (i * BLOCK_SIZE), -510.0f, 0.0f);
	}

	// �����o���h�I�u�W�F�N�g�̍쐬
	auto band = Object::Create<Band>();
	band->SetTex("asset/Texture/Band_Block.png");
	band->SetPos(30.0f, -450.0f, 0.0f);
	band->SetScale(BLOCK_SIZE, BLOCK_SIZE, 0.0f);
	band->layer = 1;
	band->SetLength(tipCount);

	// �R�C���l�����I�u�W�F�N�g�̍쐬
	auto coinNum1 = Object::Create<CoinNum>();
	auto coinNum10 = Object::Create<CoinNum>();
	auto coinNum100 = Object::Create<CoinNum>();

	// �R�C���l�����I�u�W�F�N�g�̍��W�ݒ�
	coinNum1->SetPos(150.0f, 0.0f, 0.0f);
	coinNum10->SetPos(0.0f, 0.0f, 0.0f);
	coinNum100->SetPos(-150.0f, 0.0f, 0.0f);

	// �R�C���l�����̊g��\��
	coinNum1->SetScale(150.0f, 300.0f, 0.0f);
	coinNum10->SetScale(150.0f, 300.0f, 0.0f);
	coinNum100->SetScale(150.0f, 300.0f, 0.0f);

	// �R�C���l�����I�u�W�F�N�g�̃^�O�t��
	coinNum1->tags.AddTag("��̈�");
	coinNum10->tags.AddTag("�\�̈�");
	coinNum100->tags.AddTag("�S�̈�");

	// �X�^�[�`�b�v�I�u�W�F�N�g�̍쐬
	StarTip* starTip[SET_STARTIP];
	for (int i = 0; i < SET_STARTIP; i++)
	{
		starTip[i] = Object::Create<StarTip>();
		starTip[i]->SetPos(-300.0f + (i * BLOCK_SIZE * 5), 300.0f, 0.0f);
		switch (i)
		{
		case 0:
			starTip[i]->tags.AddTag("1����");
			break;
		case 1:
			starTip[i]->tags.AddTag("2����");
			break;
		case 2:
			starTip[i]->tags.AddTag("3����");
			break;
		}
	}
	for (auto& obj : objectInstance)
	{
		obj->Init();
	}
}

// �X�V����
void ResultScene::Update()
{
	// �t�F�[�h�C������
	Fade_In();

	// ���������������ɉ����ăX�R�A���X�V
	PullScoreUpdate();

	// �R�C���l����UI�̊e���X�V����
	CoinCounter();

	// �R�C���l�����̊����ɉ�����StarTip�̊l���󋵂̍X�V
	CoinGetPercent();

	// CLEAR���S�̊g��\���ƕ\����̈ړ�
	ClearDraw();

	// UI���`��OK�Ȃ�
	if (uiFlag == true)
	{
		UI_Draw();
	}

	// �t���[���X�V����
	Frame_Update();

	// �t�F�[�h�A�E�g����	(�Â��Ȃ�)
	if (fadeOut_Start == true)
	{
		Fade_Out();
	}

	// �e�I�u�W�F�N�g�X�V����
	auto objects = objectInstance;
	for (auto& obj : objects)
	{
		if (obj->tags.SearchTag("Player"))
		{
			if (movePlayerFlag == true)
			{
				obj->Update();
			}
		}
		else
		{
			obj->Update();
		}
	}
}

// ���������������ɉ����ăX�R�A���X�V
void ResultScene::PullScoreUpdate()
{
	auto bandPullLevels = GetInstance()->GetObjects<Band>();
	for (auto& bandPullLevel : bandPullLevels)
	{
		meterCount = (int)(bandPullLevel->GetPullLevel() / -60.0f);
	}
}

// �R�C���l����UI�̊e���X�V����
void ResultScene::CoinCounter()
{
	auto coinUIs = GetInstance()->GetObjects<CoinNum>();
	for (auto& coinUI : coinUIs)
	{
		if (coinUI->tags.SearchTag("�S�̈�")) {
			int coinCount = 0;
			coinCount = meterCount / 100;
			if (coinCount >= 10) { coinCount -= 10; }
			coinUI->SetNumU(coinCount);
		}
		if (coinUI->tags.SearchTag("�\�̈�")) {
			int coinCount = 0;
			coinCount = meterCount / 10;
			if (coinCount >= 10) { coinCount -= 10; }
			coinUI->SetNumU(coinCount);
		}
		if (coinUI->tags.SearchTag("��̈�")) {
			int coinCount = 0;
			coinCount = meterCount % 10;
			coinUI->SetNumU(coinCount);
		}
	}
}

// �R�C���l�����̊����ɉ�����StarTip�̊l���󋵂̍X�V
void ResultScene::CoinGetPercent()
{
	auto star_s = GetInstance()->GetObjects<StarTip>();
	for (auto& star : star_s)
	{
		if (star->tags.SearchTag("1����"))
		{
			if (meterCount >=(GameScene::GetAllBandTipCount() * 3 / 10))
			{
				star->SetGeting(true);
			}
		}
		if (star->tags.SearchTag("2����"))
		{
			if (meterCount >= (GameScene::GetAllBandTipCount() * 6 / 10))
			{
				star->SetGeting(true);
			}
		}
		if (star->tags.SearchTag("3����"))
		{
			if (meterCount >= (GameScene::GetAllBandTipCount() * 9 / 10))
			{
				star->SetGeting(true);
			}
		}
	}
}

// CLEAR���S�̕`�揈��
void ResultScene::ClearDraw()
{
	// �o���h�I�u�W�F�N�g�̒T��
	auto bandPullLevels = GetInstance()->GetObjects<Band>();
	for (auto* bandPullLevel : bandPullLevels)
	{
		// �o���h��������������
		if ((int)(bandPullLevel->GetPullLevel() / -60.0f) >= tipCount)
		{				
			auto bandTips = GetInstance()->GetObjects<BandTip>();
			for (auto* bandTip : bandTips)
			{
				bandTip->SetVelo(0.0f, 0.0f, 0.0f);
			}
			// �v���C���[��~
			movePlayerFlag = false;
			
			// CLEAR���S�̊g��`�撆�Ȃ�
			if (drawFlag == true)
			{
				ClearBig();
			}

			// CLEAR���S���g��`�抮��������
			if (drawFlag == true &&
				drawClearFlag == true)
			{
				count += 1;
				
				// 1�b��(60frame)
				if (count >= 60)
				{
					drawFlag = false;	// �g��`�揈���I��
					moveFlag = true;	// CLEAR���S�ړ������J�n
				}
			}

			// CLEAR���S���ړ����Ȃ�
			if (moveFlag == true)
			{
				ClearMove();		// CLEAR�̃��S�k���ړ�
			}
		}
	}
}

// CLEAR�̃��S�g��\��
void ResultScene::ClearBig()
{
	auto object = GetInstance()->GetObjects<Quad>();
	for (auto& obj : object)
	{	
		// CLEAR���S�̌���
		if (obj->tags.SearchTag("CLEAR"))
		{
			// �g��o�������H
			if(obj->GetScale().x < 850.0f &&
			   obj->GetScale().y < 250.0f)
			{
				// �g��`�揈��
				obj->SetScale((obj->GetScale().x + 14.0f),
							  (obj->GetScale().y + 4.0f),
							   0.0f);
			}
			else
			{
				// �g��`�抮��
				drawClearFlag = true;	
			}
		}
	}
}

// CLEAR�̃��S�k���ړ�
void ResultScene::ClearMove()
{
	auto object = GetInstance()->GetObjects<Quad>();
	for (auto& obj : object)
	{
		// CLEAR���S�̌���
		if (obj->tags.SearchTag("CLEAR"))
		{
			// ������W�܂łɂ��Ȃ�������
			if (obj->GetPos().x > -750.0f &&
				obj->GetPos().y < 440.0f)
			{
				// �ړ�����
				obj->SetPos((obj->GetPos().x - 10.0f),
							(obj->GetPos().y + 6.0f),
							 0.0f);
			}
			// ����T�C�Y�܂ł���Ȃ�������
			if(obj->GetScale().x > 400.0f &&
			   obj->GetScale().y > 100.0f)
			{
				// �k������
				obj->SetScale((obj->GetScale().x - 6.0f),
							  (obj->GetScale().y - 2.0f),
							   0.0f);
			}
			// ����̏����ɒB������
			if (obj->GetPos().x < -750.0f ||
				obj->GetPos().y > 440.0f ||
				obj->GetScale().x < 400.0f ||
				obj->GetScale().y < 100.0f)
			{
				// �ړ���������
				moveFlag = false;
				uiFlag = true;
			}
		}
	}
}

// UI�`�揈��
void ResultScene::UI_Draw()
{
	if (layerFlag == false)
	{
		//�u�^�C�g���ɖ߂�v�̃I�u�W�F�N�g�쐬
		auto returnTitle = Object::Create<Quad>();
		returnTitle->SetTex("asset/Texture/Return_toTitle.png");	// �摜�ǂݍ���
		returnTitle->SetPos(700.0f, 0.0f, 0.0f);					// ���W��ݒ�
		returnTitle->SetScale(420.0f, 150.0f, 0.0f);				// �傫����ݒ�
		returnTitle->tags.AddTag("UI");								// �^�O�t��
		returnTitle->layer = 1;										// ���C���[��ݒ�

		//�u�X�e�[�W�I���ɖ߂�v�̃I�u�W�F�N�g�쐬
		auto returnHome = Object::Create<Quad>();
		returnHome->SetTex("asset/Texture/Return_toHome.png");		// �摜�ǂݍ���
		returnHome->SetPos(700.0f, -150.0f, 0.0f);					// ���W��ݒ�
		returnHome->SetScale(420.0f, 150.0f, 0.0f);					// �傫����ݒ�
		returnHome->tags.AddTag("UI");								// �^�O�t��
		returnHome->layer = 1;										// ���C���[��ݒ�

		//�u���g���C�v�̃I�u�W�F�N�g�쐬
		auto retryLogo = Object::Create<Quad>();
		retryLogo->SetTex("asset/Texture/Retry.png");				// �摜�ǂݍ���
		retryLogo->SetPos(700.0f, -300.0f, 0.0f);					// ���W��ݒ�
		retryLogo->SetScale(420.0f, 150.0f, 0.0f);					// �傫����ݒ�
		retryLogo->tags.AddTag("UI");								// �^�O�t��
		retryLogo->layer = 1;										// ���C���[��ݒ�

		// �t���[���I�u�W�F�N�g�쐬
		auto frame = Object::Create<Quad>();
		frame->SetTex("asset/Texture/Frame.png");					// �摜�ǂݍ���
		frame->SetPos(700.0f, 0.0f, 0.0f);							// ���W��ݒ�
		frame->SetScale(420.0f, 150.0f, 0.0f);						// �傫����ݒ�
		frame->tags.AddTag("UI");									// �^�O�t��
		frame->tags.AddTag("frame");								// �^�O�t��
		frame->layer = 1;											// ���C���[��ݒ�

		// ���C���[�`�抮��
		layerFlag = true;											
	}
}

// �t���[���X�V����
void ResultScene::Frame_Update()
{
	// �J�ڑI��
	if (movePlayerFlag == false)
	{
		Frame_Input();				// �t���[���ړ����͏���
		Frame_Move();				// �t���[���ړ�����
	}
}

// �t���[���ړ����͏���
void ResultScene::Frame_Input()
{
	/*�R���g���[���[:�\�����L�[
	 *�L�[�{�[�h�@�@:�����L�[
	 *�ǂ��炩�������ꂽ��
	 */
	if ((input.GetButtonTrigger(XINPUT_DOWN) ||
		input.GetKeyTrigger(VK_DOWN)) &&
		GetFrameNum() < 3) {
		SetFrameNum(GetFrameNum() + 1);
	}
	/*�R���g���[���[:�\����L�[
	 *�L�[�{�[�h�@�@:�����L�[
	 *�ǂ��炩�������ꂽ��
	 */
	if ((input.GetButtonTrigger(XINPUT_UP) ||
		input.GetKeyTrigger(VK_UP)) &&
		GetFrameNum() > 1) {
		SetFrameNum(GetFrameNum() - 1);
	}
}

// �t���[���ړ�����
void ResultScene::Frame_Move()
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
				quad->SetPos(700.0f, 0.0f, 0.0f);
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
				quad->SetPos(700.0f, -150.0f, 0.0f);
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
			SceneManager::ChangeScene(HOME_1, 1);
		}
		break; }
	case 3: {
		auto allQuad = GetInstance()->GetObjects<Quad>();
		for (auto& quad : allQuad)
		{
			if (quad->tags.SearchTag("frame"))
			{
				quad->SetPos(700.0f, -300.0f, 0.0f);
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
			int stageNum = (int)(GameOverScene::isEndSceneNum - SCENE_ENUM_OFFSET);
			//���݂̃V�[���𒼑O�ɃQ�[���I�[�o�[�����uGameScene�v�ɐ؂�ւ���
			SceneManager::ChangeScene(GameOverScene::isEndSceneNum, stageNum);
		}
		break; }
	default:
		break;
	}
}

// �t�F�[�h�C������		(���邭�Ȃ�)
void ResultScene::Fade_In()
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
void ResultScene::Fade_Out()
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