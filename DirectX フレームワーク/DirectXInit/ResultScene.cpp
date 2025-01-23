#include "ResultScene.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "Quad.h"
#include "Ground.h"
#include "Player.h"
#include "Band.h"
#include "CoinNum.h"
#include "StarTip.h"

#include "iostream"

int ResultScene::tipCount = 0;
int ResultScene::meterCount = 0;

void ResultScene::Init(int _num)
{
	//std::cout << "bandTipCount:" << _num << std::endl;
	tipCount = _num;
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM003);	// �T�E���h���~
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM005);	// �T�E���h���Đ�

	auto bg = Object::Create<Quad>();
	
	bg->SetTex("asset/Texture/Night.jpg");
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
	bg->layer = -1;

	auto player = Object::Create<Player>();
	player->SetPos(-800.0f, -400.0f, 0.0f);

	// CLEAR�̃��S�I�u�W�F�N�g�̍쐬
	auto clear_Logo = Object::Create<Quad>();
	clear_Logo->SetTex("asset/Texture/Clear_Logo.png");
	clear_Logo->SetPos(0.0f, 0.0f, 0.0f);
	clear_Logo->SetScale(0.0f, 0.0f, 0.0f);
	clear_Logo->tags.AddTag("CLEAR");
	clear_Logo->layer = 2;

	Ground* ground[SET_BLOCK];
	for(int i = 0; i < SET_BLOCK; i++)
	{
		ground[i] = Object::Create<Ground>();
		ground[i]->SetPos(930.0f - (i * BLOCK_SIZE), -510.0f, 0.0f);
	}

	// �����o���h�I�u�W�F�N�g�̍쐬
	auto band = Object::Create<Band>();
	band->SetTex("asset/Texture/Band_Block.png");
	band->SetPos(30.0f, -420.0f, 0.0f);
	band->SetScale(BLOCK_SIZE, BLOCK_SIZE, 0.0f);
	band->layer = 1;
	band->SetLength(tipCount+1);

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
		if (obj->tags.SearchTag("BandA"))
		{
			band->Add(obj);
		}
	}

	for (auto& obj : objectInstance)
	{
		obj->Init();
	}
}

void ResultScene::Update()
{
	// ���������������ɉ����ăX�R�A���X�V
	PullScoreUpdate();

	// �R�C���l����UI�̊e���X�V����
	CoinCounter();

	// �R�C���l�����̊����ɉ�����StarTip�̊l���󋵂̍X�V
	CoinGetPercent();

	auto bandPullLevels = GetInstance()->GetObjects<Band>();
	for (auto* bandPullLevel : bandPullLevels)
	{
		if ((int)(bandPullLevel->GetPullLevel() / -60.0f) == tipCount)
		{
			ClearDraw();
		}
	}

	auto objects = objectInstance;
	for (auto& obj : objects)
	{
		obj->Update();
	}

	// B�{�^��or�G���^�[�L�[����������
	if (input.GetButtonTrigger(XINPUT_B) || 
		input.GetKeyTrigger(VK_RETURN))
	{
		SceneManager::m_SoundManager.Play(SOUND_LABEL_SE002);
		//���݂̃V�[�����uTitleScene�v�ɐ؂�ւ���
		SceneManager::ChangeScene(TITLE);
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

void ResultScene::ClearDraw()
{
	auto object = GetInstance()->GetObjects<Quad>();
	for (auto& obj : object)
	{
		if (obj->tags.SearchTag("CLEAR"))
		{
			while(obj->GetScale().x < 850.0f &&
				  obj->GetScale().y < 250.0f)
			{
				obj->SetScale((obj->GetScale().x + 3.5f),
							  (obj->GetScale().y + 1.0f),
							   0.0f);
			}
		}
	}
}
