#include "ResultScene.h"
#include "SceneManager.h"
#include "Quad.h"
#include "Ground.h"
#include "Player.h"
#include "Band.h"
#include "CoinNum.h"

#include "iostream"

int ResultScene::count = 0;

void ResultScene::Init(int _num)
{
	//std::cout << "bandTipCount:" << _num << std::endl;
	count = _num;
	SceneManager::m_SoundManager.Stop(SOUND_LABEL_BGM003);	// �T�E���h���~
	SceneManager::m_SoundManager.Play(SOUND_LABEL_BGM005);	// �T�E���h���Đ�

	auto bg = Object::Create<Quad>();
	
	bg->SetTex("asset/Texture/Night.jpg");
	bg->SetScale(BACKGROUND_X, BACKGROUND_Y, 0.0f);
	bg->layer = -1;

	auto player = Object::Create<Player>();
	player->layer = 1;

	const int stage[OBJECT_Y_VALUE][OBJECT_X_VALUE] = {
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};


	for (int i = 0; i < OBJECT_X_VALUE; i++)
	{
		for (int j = 0; j < OBJECT_Y_VALUE; j++)
		{
			switch (stage[j][i])
			{
			case 1:
				auto ground = Object::Create<Ground>();
				ground->SetPos(GROUND_OFFSET_X + i * BLOCK_SIZE, -(GROUND_OFFSET_Y + j * BLOCK_SIZE), 0.0f);	// ���W��������

				if (47<=i && i<=(47+count))
				{
					ground->tags.AddTag("BandA");
				}
				break;
			}
		}
	}

	auto band = Object::Create<Band>();
	band->SetTex("asset/Texture/Band_Block.png");
	band->SetPos(30.0f, -420.0f, 0.0f);
	band->SetScale(BLOCK_SIZE, BLOCK_SIZE, 0.0f);
	band->layer = 1;
	band->SetLength(count);

	// �R�C���l�����I�u�W�F�N�g�̍쐬
	auto coinNum1 = Object::Create<CoinNum>();
	auto coinNum10 = Object::Create<CoinNum>();
	auto coinNum100 = Object::Create<CoinNum>();

	// �R�C���l�����I�u�W�F�N�g�̍��W�ݒ�
	coinNum1->SetPos(50.0f, 0.0f, 0.0f);
	coinNum10->SetPos(0.0f, 0.0f, 0.0f);
	coinNum100->SetPos(-50.0f, 0.0f, 0.0f);

	// �R�C���l�����I�u�W�F�N�g�̃^�O�t��
	coinNum1->tags.AddTag("1");
	coinNum10->tags.AddTag("10");
	coinNum100->tags.AddTag("100");

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
	// �R�C���l����UI�̊e���X�V����
	auto coinUIs = GetInstance()->GetObjects<CoinNum>();
	for (auto& coinUI : coinUIs)
	{
		if (coinUI->tags.SearchTag("100")) {
			int coinCount = 0;
			coinCount = count / 100;
			if (coinCount >= 10) { coinCount -= 10; }
			coinUI->SetNumU(coinCount);
		}
		if (coinUI->tags.SearchTag("10")) {
			int coinCount = 0;
			coinCount = count / 10;
			if (coinCount >= 10) { coinCount -= 10; }
			coinUI->SetNumU(coinCount);
		}

		if (coinUI->tags.SearchTag("1")) {
			int coinCount = 0;
			coinCount = count % 10;
			coinUI->SetNumU(coinCount);
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

	auto players = GetInstance()->GetObjects<Player>();
	for (auto& player : players)
	{
		if (GROUND_OFFSET_Y > player->GetPos().y + 120.0f)
		{
			SceneManager::ChangeScene(TITLE);
		}
	}
}