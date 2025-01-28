#include "GameScene.h"
#include "GameOverScene.h"
#include "SceneManager.h"
#include "Quad.h"
#include "Ground.h"
#include "Player.h"
#include "Band.h"
#include "Coin.h"
#include "CoinNum.h"
#include "Goal.h"
#include "MapEditor.h"

//#include "iostream"

Player* GameScene::player = nullptr;

int GameScene::bandTipCount = 0;			// bandTip�̊l����
int GameScene::allBandTipCount = 0;			// bandTip�̑���

void GameScene::Init(int _num)
{	
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// �T�E���h���~
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// �T�E���h���~
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM005);	// �T�E���h���~
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// �T�E���h���Đ�

	bandTipCount = 0;		// �l������������
	allBandTipCount = 0;	// �X�e�[�W���ɂ���R�C���̑���
	gameSceneNum = _num;
	GameOverScene::isEndSceneNum = (SCENE)(gameSceneNum + SCENE_ENUM_OFFSET);
	switch(gameSceneNum)
	{
	case 1: {

		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_1.jpg");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -2;

		// �t�F�[�h�C���E�t�F�[�h�A�E�g�p
		auto fade = Object::Create<Quad>();	
		fade->SetTex("asset/Texture/Fade_Black.png",			// �摜�ǂݍ���
			1, 1, 0, 0, 1.0f, 1.0f, 1.0f, 1.0f);
		fade->SetPos(0.0f, 0.0f, 0.0f);							// ���W�ݒ�
		fade->SetScale(1920.0f, 1080.0f, 0.0f);					// �傫����ݒ�
		fade->tags.AddTag("Fade");								// �^�O�t��
		fade->layer = 10;										// ���C���[��ݒ�

		// Stage1��CSV�ǂݍ���
		MapEditor::Load("Stage1.csv");
		
		// �R�C���l�����I�u�W�F�N�g�̍쐬
		auto coinNum1	= Object::Create<CoinNum>();
		auto coinNum10	= Object::Create<CoinNum>();
		auto coinNum100 = Object::Create<CoinNum>();
		
		// �R�C���l�����I�u�W�F�N�g�̍��W�ݒ�
		coinNum1	->SetPos(900.0f, 480.0f, 0.0f);
		coinNum10	->SetPos(840.0f, 480.0f, 0.0f);
		coinNum100	->SetPos(780.0f, 480.0f, 0.0f);
		
		// �R�C���l�����I�u�W�F�N�g�̑傫����ݒ�
		coinNum1	->SetScale(50.0f, 100.0f, 0.0f);						
		coinNum10	->SetScale(50.0f, 100.0f, 0.0f);
		coinNum100	->SetScale(50.0f, 100.0f, 0.0f);

		// �R�C���l�����I�u�W�F�N�g�̃^�O�t��
		coinNum1	->tags.AddTag("��̈�");
		coinNum10	->tags.AddTag("�\�̈�");
		coinNum100	->tags.AddTag("�S�̈�");
		
		break; }
	case 2: {

		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_2.png");
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

		// Stage2��CSV�ǂݍ���

		// �R�C���l�����I�u�W�F�N�g�̍쐬
		auto coinNum1 = Object::Create<CoinNum>();
		auto coinNum10 = Object::Create<CoinNum>();
		auto coinNum100 = Object::Create<CoinNum>();

		// �R�C���l�����I�u�W�F�N�g�̍��W�ݒ�
		coinNum1->SetPos(900.0f, 480.0f, 0.0f);
		coinNum10->SetPos(840.0f, 480.0f, 0.0f);
		coinNum100->SetPos(780.0f, 480.0f, 0.0f);

		// �R�C���l�����I�u�W�F�N�g�̑傫����ݒ�
		coinNum1->SetScale(50.0f, 100.0f, 0.0f);
		coinNum10->SetScale(50.0f, 100.0f, 0.0f);
		coinNum100->SetScale(50.0f, 100.0f, 0.0f);

		// �R�C���l�����I�u�W�F�N�g�̃^�O�t��
		coinNum1->tags.AddTag("��̈�");
		coinNum10->tags.AddTag("�\�̈�");
		coinNum100->tags.AddTag("�S�̈�");

		break; }
	case 3: {
	
		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_3.jpg");
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
		
		// Stage3��CSV�ǂݍ���

		// �R�C���l�����I�u�W�F�N�g�̍쐬
		auto coinNum1 = Object::Create<CoinNum>();
		auto coinNum10 = Object::Create<CoinNum>();
		auto coinNum100 = Object::Create<CoinNum>();

		// �R�C���l�����I�u�W�F�N�g�̍��W�ݒ�
		coinNum1->SetPos(900.0f, 480.0f, 0.0f);
		coinNum10->SetPos(840.0f, 480.0f, 0.0f);
		coinNum100->SetPos(780.0f, 480.0f, 0.0f);

		// �R�C���l�����I�u�W�F�N�g�̑傫����ݒ�
		coinNum1->SetScale(50.0f, 100.0f, 0.0f);
		coinNum10->SetScale(50.0f, 100.0f, 0.0f);
		coinNum100->SetScale(50.0f, 100.0f, 0.0f);

		// �R�C���l�����I�u�W�F�N�g�̃^�O�t��
		coinNum1->tags.AddTag("��̈�");
		coinNum10->tags.AddTag("�\�̈�");
		coinNum100->tags.AddTag("�S�̈�");

		break; }
	case 4: {
	
		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_4.png");
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

		// Stage4��CSV�ǂݍ���

		// �R�C���l�����I�u�W�F�N�g�̍쐬
		auto coinNum1 = Object::Create<CoinNum>();
		auto coinNum10 = Object::Create<CoinNum>();
		auto coinNum100 = Object::Create<CoinNum>();

		// �R�C���l�����I�u�W�F�N�g�̍��W�ݒ�
		coinNum1->SetPos(900.0f, 480.0f, 0.0f);
		coinNum10->SetPos(840.0f, 480.0f, 0.0f);
		coinNum100->SetPos(780.0f, 480.0f, 0.0f);

		// �R�C���l�����I�u�W�F�N�g�̑傫����ݒ�
		coinNum1->SetScale(50.0f, 100.0f, 0.0f);
		coinNum10->SetScale(50.0f, 100.0f, 0.0f);
		coinNum100->SetScale(50.0f, 100.0f, 0.0f);

		// �R�C���l�����I�u�W�F�N�g�̃^�O�t��
		coinNum1->tags.AddTag("��̈�");
		coinNum10->tags.AddTag("�\�̈�");
		coinNum100->tags.AddTag("�S�̈�");
		break; }
	case 5: {
		
		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_5.jpg");
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

		// Stage5��CSV�ǂݍ���

		// �R�C���l�����I�u�W�F�N�g�̍쐬
		auto coinNum1 = Object::Create<CoinNum>();
		auto coinNum10 = Object::Create<CoinNum>();
		auto coinNum100 = Object::Create<CoinNum>();

		// �R�C���l�����I�u�W�F�N�g�̍��W�ݒ�
		coinNum1->SetPos(900.0f, 480.0f, 0.0f);
		coinNum10->SetPos(840.0f, 480.0f, 0.0f);
		coinNum100->SetPos(780.0f, 480.0f, 0.0f);

		// �R�C���l�����I�u�W�F�N�g�̑傫����ݒ�
		coinNum1->SetScale(50.0f, 100.0f, 0.0f);
		coinNum10->SetScale(50.0f, 100.0f, 0.0f);
		coinNum100->SetScale(50.0f, 100.0f, 0.0f);

		// �R�C���l�����I�u�W�F�N�g�̃^�O�t��
		coinNum1->tags.AddTag("��̈�");
		coinNum10->tags.AddTag("�\�̈�");
		coinNum100->tags.AddTag("�S�̈�");

		break; }
	case 6: {
		
		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_6.png");
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

		// Stage6��CSV�ǂݍ���

		// �R�C���l�����I�u�W�F�N�g�̍쐬
		auto coinNum1 = Object::Create<CoinNum>();
		auto coinNum10 = Object::Create<CoinNum>();
		auto coinNum100 = Object::Create<CoinNum>();

		// �R�C���l�����I�u�W�F�N�g�̍��W�ݒ�
		coinNum1->SetPos(900.0f, 480.0f, 0.0f);
		coinNum10->SetPos(840.0f, 480.0f, 0.0f);
		coinNum100->SetPos(780.0f, 480.0f, 0.0f);

		// �R�C���l�����I�u�W�F�N�g�̑傫����ݒ�
		coinNum1->SetScale(50.0f, 100.0f, 0.0f);
		coinNum10->SetScale(50.0f, 100.0f, 0.0f);
		coinNum100->SetScale(50.0f, 100.0f, 0.0f);

		// �R�C���l�����I�u�W�F�N�g�̃^�O�t��
		coinNum1->tags.AddTag("��̈�");
		coinNum10->tags.AddTag("�\�̈�");
		coinNum100->tags.AddTag("�S�̈�");

		break; }
	case 7: {
	
		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_7.jpg");
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

		// Stage7��CSV�ǂݍ���

		// �R�C���l�����I�u�W�F�N�g�̍쐬
		auto coinNum1 = Object::Create<CoinNum>();
		auto coinNum10 = Object::Create<CoinNum>();
		auto coinNum100 = Object::Create<CoinNum>();

		// �R�C���l�����I�u�W�F�N�g�̍��W�ݒ�
		coinNum1->SetPos(900.0f, 480.0f, 0.0f);
		coinNum10->SetPos(840.0f, 480.0f, 0.0f);
		coinNum100->SetPos(780.0f, 480.0f, 0.0f);

		// �R�C���l�����I�u�W�F�N�g�̑傫����ݒ�
		coinNum1->SetScale(50.0f, 100.0f, 0.0f);
		coinNum10->SetScale(50.0f, 100.0f, 0.0f);
		coinNum100->SetScale(50.0f, 100.0f, 0.0f);

		// �R�C���l�����I�u�W�F�N�g�̃^�O�t��
		coinNum1->tags.AddTag("��̈�");
		coinNum10->tags.AddTag("�\�̈�");
		coinNum100->tags.AddTag("�S�̈�");

		break; }
	case 8: {
	
		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_8.png");
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

		// Stage8��CSV�ǂݍ���

		// �R�C���l�����I�u�W�F�N�g�̍쐬
		auto coinNum1 = Object::Create<CoinNum>();
		auto coinNum10 = Object::Create<CoinNum>();
		auto coinNum100 = Object::Create<CoinNum>();

		// �R�C���l�����I�u�W�F�N�g�̍��W�ݒ�
		coinNum1->SetPos(900.0f, 480.0f, 0.0f);
		coinNum10->SetPos(840.0f, 480.0f, 0.0f);
		coinNum100->SetPos(780.0f, 480.0f, 0.0f);

		// �R�C���l�����I�u�W�F�N�g�̑傫����ݒ�
		coinNum1->SetScale(50.0f, 100.0f, 0.0f);
		coinNum10->SetScale(50.0f, 100.0f, 0.0f);
		coinNum100->SetScale(50.0f, 100.0f, 0.0f);

		// �R�C���l�����I�u�W�F�N�g�̃^�O�t��
		coinNum1->tags.AddTag("��̈�");
		coinNum10->tags.AddTag("�\�̈�");
		coinNum100->tags.AddTag("�S�̈�");

		break; }
	default:
		break;
	}
}

void GameScene::Update()
{
	// �t�F�[�h�C������		(���邭�Ȃ�)
	Fade_In();		
	// �R�C���l����UI�̊e���X�V����
	CoinCounter();
	// �R�C���l����UI�̊e���X�V����
	FallIsPlayer();
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

// �R�C���l����UI�̊e���X�V����
void GameScene::CoinCounter()
{
	auto coinUIs = GetInstance()->GetObjects<CoinNum>();
	for (auto& coinUI : coinUIs)
	{
		if (coinUI->tags.SearchTag("�S�̈�")) {
			int coinCount = 0;
			coinCount = GameScene::bandTipCount / 100;
			if (coinCount >= 10) { coinCount -= 10; }
			coinUI->SetNumU(coinCount);
		}
		if (coinUI->tags.SearchTag("�\�̈�")) {
			int coinCount = 0;
			coinCount = GameScene::bandTipCount / 10;
			if (coinCount >= 10) { coinCount -= 10; }
			coinUI->SetNumU(coinCount);
		}

		if (coinUI->tags.SearchTag("��̈�")) {
			int coinCount = 0;
			coinCount = GameScene::bandTipCount % 10;
			coinUI->SetNumU(coinCount);
		}
	}
}

// player�̗������菈���ƑJ�ڏ���
void GameScene::FallIsPlayer()
{
	auto players = GetInstance()->GetObjects<Player>();
	for (auto& player : players)
	{
		if (GROUND_OFFSET_Y > player->GetPos().y + 120.0f)
		{
			fadeOut_Start = true;
		}
	}
	if (fadeOut_End == true)
	{
		SceneManager::ChangeScene(GAMEOVER);
	}
}


// �t�F�[�h�C������		(���邭�Ȃ�)
void GameScene::Fade_In()
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
void GameScene::Fade_Out()
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