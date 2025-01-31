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
#include "Application.h"

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
		bg->layer = -5;

		// �t�F�[�h�C���E�t�F�[�h�A�E�g
		auto fade = Object::Create<Quad>();
		fade->SetTex("asset/Texture/Fade.png");						// �摜�ǂݍ���
		fade->SetPos(0.0f, 0.0f, 0.0f);								// ���W�ݒ�
		fade->SetScale(1920.0f, 1080.0f, 0.0f);						// �傫����ݒ�
		fade->tags.AddTag("Fade");									// �^�O�t��
		fade->layer = 10;											// ���C���[��ݒ�

		// �t�F�[�h�C���E�t�F�[�h�A�E�g(�Q�[���I�[�o�[)	
		auto fade_GameOver = Object::Create<Quad>();
		fade_GameOver->SetTex("asset/Texture/Fade_Black.png");			// �摜�ǂݍ���
		fade_GameOver->SetPos(0.0f, 0.0f, 0.0f);						// ���W�ݒ�
		fade_GameOver->SetScale(1920.0f, 1080.0f, 0.0f);				// �傫����ݒ�
		fade_GameOver->SetColor(1.0f, 1.0f, 1.0f, 0.0f);				// �F�ݒ�
		fade_GameOver->tags.AddTag("Fade_GameOver");					// �^�O�t��
		fade_GameOver->layer = -10;										// ���C���[��ݒ�

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
		
		// ���g���CUI�\���I�u�W�F�N�g�쐬
		auto retry = Object::Create<Quad>();
		retry->SetTex("asset/Texture/Retry_UI.png");			// �摜�ǂݍ���
		retry->SetPos(-900.0f, 480.0f, 0.0f);					// ���W�ݒ�
		retry->SetScale(100.0f, 100.0f, 100.0f);				// �傫����ݒ�
		retry->tags.AddTag("Retry");							// �^�O�t��

		break; }
	case 2: {

		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_2.png");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -5;

		// �t�F�[�h�C���E�t�F�[�h�A�E�g
		auto fade = Object::Create<Quad>();
		fade->SetTex("asset/Texture/Fade.png");						// �摜�ǂݍ���
		fade->SetPos(0.0f, 0.0f, 0.0f);								// ���W�ݒ�
		fade->SetScale(1920.0f, 1080.0f, 0.0f);						// �傫����ݒ�
		fade->tags.AddTag("Fade");									// �^�O�t��
		fade->layer = 10;											// ���C���[��ݒ�

		// �t�F�[�h�C���E�t�F�[�h�A�E�g(�Q�[���I�[�o�[)	
		auto fade_GameOver = Object::Create<Quad>();
		fade_GameOver->SetTex("asset/Texture/Fade_Black.png",			// �摜�ǂݍ���
			1, 1, 0, 0, 1.0f, 1.0f, 1.0f, 0.0f);
		fade_GameOver->SetPos(0.0f, 0.0f, 0.0f);						// ���W�ݒ�
		fade_GameOver->SetScale(1920.0f, 1080.0f, 0.0f);				// �傫����ݒ�
		fade_GameOver->tags.AddTag("Fade_GameOver");					// �^�O�t��
		fade_GameOver->layer = -10;										// ���C���[��ݒ�

		// Stage2��CSV�ǂݍ���
		MapEditor::Load("Stage2.csv");

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

		// ���g���CUI�\���I�u�W�F�N�g�쐬
		auto retry = Object::Create<Quad>();					// �摜�ǂݍ���
		retry->SetTex("asset/Texture/Retry_UI.png");			// �摜�ǂݍ���
		retry->SetPos(-900.0f, 480.0f, 0.0f);					// ���W�ݒ�
		retry->SetScale(100.0f, 100.0f, 100.0f);				// �傫����ݒ�
		retry->tags.AddTag("Retry");							// �^�O�t��

		break; }
	case 3: {
	
		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_3.jpg");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -5;

		// �t�F�[�h�C���E�t�F�[�h�A�E�g
		auto fade = Object::Create<Quad>();
		fade->SetTex("asset/Texture/Fade.png");						// �摜�ǂݍ���
		fade->SetPos(0.0f, 0.0f, 0.0f);								// ���W�ݒ�
		fade->SetScale(1920.0f, 1080.0f, 0.0f);						// �傫����ݒ�
		fade->tags.AddTag("Fade");									// �^�O�t��
		fade->layer = 10;											// ���C���[��ݒ�
		
		// �t�F�[�h�C���E�t�F�[�h�A�E�g(�Q�[���I�[�o�[)	
		auto fade_GameOver = Object::Create<Quad>();
		fade_GameOver->SetTex("asset/Texture/Fade_Black.png",			// �摜�ǂݍ���
			1, 1, 0, 0, 1.0f, 1.0f, 1.0f, 0.0f);
		fade_GameOver->SetPos(0.0f, 0.0f, 0.0f);						// ���W�ݒ�
		fade_GameOver->SetScale(1920.0f, 1080.0f, 0.0f);				// �傫����ݒ�
		fade_GameOver->tags.AddTag("Fade_GameOver");					// �^�O�t��
		fade_GameOver->layer = -10;										// ���C���[��ݒ�

		// Stage3��CSV�ǂݍ���
		MapEditor::Load("Stage3.csv");

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

		// ���g���CUI�\���I�u�W�F�N�g�쐬
		auto retry = Object::Create<Quad>();					// �摜�ǂݍ���
		retry->SetTex("asset/Texture/Retry_UI.png");			// �摜�ǂݍ���
		retry->SetPos(-900.0f, 480.0f, 0.0f);					// ���W�ݒ�
		retry->SetScale(100.0f, 100.0f, 100.0f);				// �傫����ݒ�
		retry->tags.AddTag("Retry");							// �^�O�t��

		break; }
	case 4: {
	
		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_4.png");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -5;

		// �t�F�[�h�C���E�t�F�[�h�A�E�g
		auto fade = Object::Create<Quad>();
		fade->SetTex("asset/Texture/Fade.png");						// �摜�ǂݍ���
		fade->SetPos(0.0f, 0.0f, 0.0f);								// ���W�ݒ�
		fade->SetScale(1920.0f, 1080.0f, 0.0f);						// �傫����ݒ�
		fade->tags.AddTag("Fade");									// �^�O�t��
		fade->layer = 10;											// ���C���[��ݒ�

		// �t�F�[�h�C���E�t�F�[�h�A�E�g(�Q�[���I�[�o�[)	
		auto fade_GameOver = Object::Create<Quad>();
		fade_GameOver->SetTex("asset/Texture/Fade_Black.png",			// �摜�ǂݍ���
			1, 1, 0, 0, 1.0f, 1.0f, 1.0f, 0.0f);
		fade_GameOver->SetPos(0.0f, 0.0f, 0.0f);						// ���W�ݒ�
		fade_GameOver->SetScale(1920.0f, 1080.0f, 0.0f);				// �傫����ݒ�
		fade_GameOver->tags.AddTag("Fade_GameOver");					// �^�O�t��
		fade_GameOver->layer = -10;										// ���C���[��ݒ�

		// Stage4��CSV�ǂݍ���
		MapEditor::Load("Stage4.csv");

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

		// ���g���CUI�\���I�u�W�F�N�g�쐬
		auto retry = Object::Create<Quad>();					// �摜�ǂݍ���
		retry->SetTex("asset/Texture/Retry_UI.png");			// �摜�ǂݍ���
		retry->SetPos(-900.0f, 480.0f, 0.0f);					// ���W�ݒ�
		retry->SetScale(100.0f, 100.0f, 100.0f);				// �傫����ݒ�
		retry->tags.AddTag("Retry");							// �^�O�t��

		break; }
	case 5: {
		
		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_5.jpg");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -5;
		
		// �t�F�[�h�C���E�t�F�[�h�A�E�g
		auto fade = Object::Create<Quad>();
		fade->SetTex("asset/Texture/Fade.png");						// �摜�ǂݍ���
		fade->SetPos(0.0f, 0.0f, 0.0f);								// ���W�ݒ�
		fade->SetScale(1920.0f, 1080.0f, 0.0f);						// �傫����ݒ�
		fade->tags.AddTag("Fade");									// �^�O�t��
		fade->layer = 10;											// ���C���[��ݒ�

		// �t�F�[�h�C���E�t�F�[�h�A�E�g(�Q�[���I�[�o�[)	
		auto fade_GameOver = Object::Create<Quad>();
		fade_GameOver->SetTex("asset/Texture/Fade_Black.png",			// �摜�ǂݍ���
			1, 1, 0, 0, 1.0f, 1.0f, 1.0f, 0.0f);
		fade_GameOver->SetPos(0.0f, 0.0f, 0.0f);						// ���W�ݒ�
		fade_GameOver->SetScale(1920.0f, 1080.0f, 0.0f);				// �傫����ݒ�
		fade_GameOver->tags.AddTag("Fade_GameOver");					// �^�O�t��
		fade_GameOver->layer = -10;										// ���C���[��ݒ�

		// Stage5��CSV�ǂݍ���
		MapEditor::Load("Stage5.csv");

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

		// ���g���CUI�\���I�u�W�F�N�g�쐬
		auto retry = Object::Create<Quad>();					// �摜�ǂݍ���
		retry->SetTex("asset/Texture/Retry_UI.png");			// �摜�ǂݍ���
		retry->SetPos(-900.0f, 480.0f, 0.0f);					// ���W�ݒ�
		retry->SetScale(100.0f, 100.0f, 100.0f);				// �傫����ݒ�
		retry->tags.AddTag("Retry");							// �^�O�t��

		break; }
	case 6: {
		
		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_6.png");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -5;

		// �t�F�[�h�C���E�t�F�[�h�A�E�g
		auto fade = Object::Create<Quad>();
		fade->SetTex("asset/Texture/Fade.png");						// �摜�ǂݍ���
		fade->SetPos(0.0f, 0.0f, 0.0f);								// ���W�ݒ�
		fade->SetScale(1920.0f, 1080.0f, 0.0f);						// �傫����ݒ�
		fade->tags.AddTag("Fade");									// �^�O�t��
		fade->layer = 10;											// ���C���[��ݒ�

		// �t�F�[�h�C���E�t�F�[�h�A�E�g(�Q�[���I�[�o�[)	
		auto fade_GameOver = Object::Create<Quad>();
		fade_GameOver->SetTex("asset/Texture/Fade_Black.png",			// �摜�ǂݍ���
			1, 1, 0, 0, 1.0f, 1.0f, 1.0f, 0.0f);
		fade_GameOver->SetPos(0.0f, 0.0f, 0.0f);						// ���W�ݒ�
		fade_GameOver->SetScale(1920.0f, 1080.0f, 0.0f);				// �傫����ݒ�
		fade_GameOver->tags.AddTag("Fade_GameOver");					// �^�O�t��
		fade_GameOver->layer = -10;										// ���C���[��ݒ�

		// Stage6��CSV�ǂݍ���
		MapEditor::Load("Stage6.csv");

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

		// ���g���CUI�\���I�u�W�F�N�g�쐬
		auto retry = Object::Create<Quad>();					// �摜�ǂݍ���
		retry->SetTex("asset/Texture/Retry_UI.png");			// �摜�ǂݍ���
		retry->SetPos(-900.0f, 480.0f, 0.0f);					// ���W�ݒ�
		retry->SetScale(100.0f, 100.0f, 100.0f);				// �傫����ݒ�
		retry->tags.AddTag("Retry");							// �^�O�t��

		break; }
	case 7: {
	
		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_7.jpg");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -5;

		// �t�F�[�h�C���E�t�F�[�h�A�E�g
		auto fade = Object::Create<Quad>();
		fade->SetTex("asset/Texture/Fade.png");						// �摜�ǂݍ���
		fade->SetPos(0.0f, 0.0f, 0.0f);								// ���W�ݒ�
		fade->SetScale(1920.0f, 1080.0f, 0.0f);						// �傫����ݒ�
		fade->tags.AddTag("Fade");									// �^�O�t��
		fade->layer = 10;											// ���C���[��ݒ�

		// �t�F�[�h�C���E�t�F�[�h�A�E�g(�Q�[���I�[�o�[)	
		auto fade_GameOver = Object::Create<Quad>();
		fade_GameOver->SetTex("asset/Texture/Fade_Black.png",			// �摜�ǂݍ���
			1, 1, 0, 0, 1.0f, 1.0f, 1.0f, 0.0f);
		fade_GameOver->SetPos(0.0f, 0.0f, 0.0f);						// ���W�ݒ�
		fade_GameOver->SetScale(1920.0f, 1080.0f, 0.0f);				// �傫����ݒ�
		fade_GameOver->tags.AddTag("Fade_GameOver");					// �^�O�t��
		fade_GameOver->layer = -10;										// ���C���[��ݒ�

		// Stage7��CSV�ǂݍ���
		MapEditor::Load("Stage7.csv");

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

		// ���g���CUI�\���I�u�W�F�N�g�쐬
		auto retry = Object::Create<Quad>();					// �摜�ǂݍ���
		retry->SetTex("asset/Texture/Retry_UI.png");			// �摜�ǂݍ���
		retry->SetPos(-900.0f, 480.0f, 0.0f);					// ���W�ݒ�
		retry->SetScale(100.0f, 100.0f, 100.0f);				// �傫����ݒ�
		retry->tags.AddTag("Retry");							// �^�O�t��

		break; }
	case 8: {
	
		// �w�i�I�u�W�F�N�g�̍쐬
		auto bg = Object::Create<Quad>();
		bg->SetTex("asset/Texture/Game_8.png");
		bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
		bg->layer = -5;

		// �t�F�[�h�C���E�t�F�[�h�A�E�g
		auto fade = Object::Create<Quad>();
		fade->SetTex("asset/Texture/Fade.png");						// �摜�ǂݍ���
		fade->SetPos(0.0f, 0.0f, 0.0f);								// ���W�ݒ�
		fade->SetScale(1920.0f, 1080.0f, 0.0f);						// �傫����ݒ�
		fade->tags.AddTag("Fade");									// �^�O�t��
		fade->layer = 10;											// ���C���[��ݒ�

		// �t�F�[�h�C���E�t�F�[�h�A�E�g(�Q�[���I�[�o�[)	
		auto fade_GameOver = Object::Create<Quad>();
		fade_GameOver->SetTex("asset/Texture/Fade_Black.png",			// �摜�ǂݍ���
			1, 1, 0, 0, 1.0f, 1.0f, 1.0f, 0.0f);
		fade_GameOver->SetPos(0.0f, 0.0f, 0.0f);						// ���W�ݒ�
		fade_GameOver->SetScale(1920.0f, 1080.0f, 0.0f);				// �傫����ݒ�
		fade_GameOver->tags.AddTag("Fade_GameOver");					// �^�O�t��
		fade_GameOver->layer = -10;										// ���C���[��ݒ�

		// Stage8��CSV�ǂݍ���
		MapEditor::Load("Stage8.csv");

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

		// ���g���CUI�\���I�u�W�F�N�g�쐬
		auto retry = Object::Create<Quad>();					// �摜�ǂݍ���
		retry->SetTex("asset/Texture/Retry_UI.png");			// �摜�ǂݍ���
		retry->SetPos(-900.0f, 480.0f, 0.0f);					// ���W�ݒ�
		retry->SetScale(100.0f, 100.0f, 100.0f);				// �傫����ݒ�
		retry->tags.AddTag("Retry");							// �^�O�t��

		break; }
	default:
		break;
	}
}

void GameScene::Update()
{
	if (fade_In == true)
	{
		// �t�F�[�h�C������		(���邭�Ȃ�)
		Fade_In();
	}
	// �R�C���l����UI�̊e���X�V����
	CoinCounter();
	// �R�C���l����UI�̊e���X�V����
	FallIsPlayer();
	// �Q�[�����̃��g���C�@�\
	RetryGame();
	if (fadeOut_Start == true)
	{
		Fade_Out();	// �t�F�[�h�A�E�g����	(�Â��Ȃ�)
	}
	if (fadeOut_Start_GameOver == true)
	{
		Fade_Out_GameOver();	// �t�F�[�h�A�E�g(�Q�[���I�[�o�[)
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
			fadeOut_Start_GameOver = true;
		}
	}
	if (fadeOut_End_GameOver == true)
	{
		SceneManager::ChangeScene(GAMEOVER);
	}
}


// �t�F�[�h�C������		(���邭�Ȃ�)
void GameScene::Fade_In()
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
void GameScene::Fade_Out()
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

// �Q�[�����̃��g���C�@�\
void GameScene::RetryGame()
{
	if(input.GetKeyTrigger(VK_R)||
	   input.GetButtonTrigger(XINPUT_START))
	{
		int stageNum = (int)(GameOverScene::isEndSceneNum - SCENE_ENUM_OFFSET);					
		SceneManager::ChangeScene(GameOverScene::isEndSceneNum, stageNum);
	}
}

void GameScene::Fade_Out_GameOver()
{
	auto Fade = GetInstance()->GetObjects<Quad>();
	for (auto& fade : Fade)
	{
		if (fade->tags.SearchTag("Fade_GameOver"))
		{
			fade->layer = 10;
			if (fade->GetColor().w <= 1.0f)
			{
				fade->SetColor(1.0f, 1.0f, 1.0f, fade->GetColor().w + 0.05f);
			}
			else
			{
				fadeOut_End_GameOver = true;
			}
		}
	}
}