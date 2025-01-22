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

//#include "iostream"

int GameScene::bandTipCount = 0;			// bandTip�̊l����
int GameScene::allBandTipCount = SET_COIN;	// bandTip�̑���

void GameScene::Init(int _num)
{	
	bandTipCount = 0;
	gameSceneNum = _num;
	GameOverScene::isEndSceneNum = (SCENE)(gameSceneNum + SCENE_ENUM_OFFSET);
	switch(gameSceneNum)
	{
	case 1: {
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// �T�E���h���~
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// �T�E���h���~
		SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// �T�E���h���Đ�

		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_1.jpg");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -1;

		// Stage1��CSV�ǂݍ���
		
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
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// �T�E���h���~
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// �T�E���h���~
		SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// �T�E���h���Đ�

		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_2.png");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -1;

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
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// �T�E���h���~
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// �T�E���h���~
		SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// �T�E���h���Đ�

		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_3.jpg");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -1;
		
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
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// �T�E���h���~
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// �T�E���h���~
		SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// �T�E���h���Đ�

		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_4.png");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -1;

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
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// �T�E���h���~
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// �T�E���h���~
		SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// �T�E���h���Đ�

		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_5.jpg");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -1;
		
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
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// �T�E���h���~
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// �T�E���h���~
		SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// �T�E���h���Đ�

		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_6.png");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -1;

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
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// �T�E���h���~
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// �T�E���h���~
		SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// �T�E���h���Đ�

		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_7.jpg");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -1;

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
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM002);	// �T�E���h���~
		SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM004);	// �T�E���h���~
		SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM003);	// �T�E���h���Đ�

		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_8.png");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -1;

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
	// �R�C���l����UI�̊e���X�V����
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

	auto objects = objectInstance;
	for (auto& obj : objects)
	{
		obj->Update();
	}

	auto players =GetInstance()->GetObjects<Player>();
	for (auto& player : players)
	{
		if (GROUND_OFFSET_Y > player->GetPos().y + 120.0f)
		{
			SceneManager::ChangeScene(GAMEOVER);
		}
	}
}
