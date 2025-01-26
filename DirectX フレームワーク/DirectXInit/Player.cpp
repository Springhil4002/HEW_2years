#include "Player.h"
#include "Ground.h"
#include "Band.h"
#include "Application.h"
using namespace DirectX::SimpleMath;

#define GROUND_OFFSET_X (-930.0f)
#define GROUND_OFFSET_Y (-510.0f)

//===================================================================
// コンストラクタ
//===================================================================
Player::Player() : velocity(1.5f), gravity(3.0f), jumpSpeed(50.0f), isJumping(true), isFalling(false), isGrabing(false), isMoving(false)
{

}

//===================================================================
// 初期化処理
//===================================================================
void Player::Init()
{
	SetTex("asset/Texture/Player_Animation.png",6,1,0,0);			// プレイヤーを初期化
	SetScale(BLOCK_SIZE, 2 * BLOCK_SIZE, 0.0f);				// 大きさを設定
	tags.AddTag("Player");
	layer = 10;				
	m_Acceleration.y = -gravity;
}

//===================================================================
// 更新処理
//===================================================================
void Player::Update()
{	
	State();	// 状態管理

	Walk();		// 歩き処理
	Jump();		// 跳躍処理
	Resist();	// 抵抗処理
	Entity::Update();	// 衝突処理

	auto allQuad = Scene::GetInstance()->GetObjects<Quad>();
	for (auto& x : allQuad)
	{
		if (x->tags.SearchTag("check"))
		{
			if ((Scene::input.GetButtonRelease(XINPUT_RIGHT_TRIGGER) ||
				Scene::input.GetButtonRelease(XINPUT_LEFT_TRIGGER)))
			{
				x->SetPos(200, 0, 0);
			}
			else
			{
				x->SetPos(0, 0, 0);
			}

			break;
		}
	}

}

//===================================================================
// プレイヤーの状態遷移処理
//===================================================================
void Player::State() {
	if (m_Velocity.y < -0.001f)
	{
		state = FALLING;
	}

	if (m_Velocity.y > 0.001f)
	{
		state = FLYING;
	}

	if (state == FALLING && -0.001f < m_Velocity.y && m_Velocity.y < 0.001f)
	{
		state = ONGROUND;
	}

	if (Scene::input.GetKeyPress(VK_E) ||
	   (Scene::input.GetLeftTrigger()>=0.9 &&
		Scene::input.GetRightTrigger()>=0.9 ) )
	{
		auto allBandTip = Scene::GetInstance()->GetObjects<BandTip>();
		for (auto& bandTip : allBandTip)
		{
			if (Object::Collision(this, bandTip))
			{
				if (moveDirection == bandTip->MoveDirection())
				{
					grabState = GRAB;
					SceneManager::m_SoundManager.Play(SOUND_LABEL_SE006);	// 掴む音
					if (m_Velocity.x > -0.01f && moveDirection == LEFT || m_Velocity.x < 0.01f && moveDirection == RIGHT)
					{
						bandTip->isGrabing = true;
						bandTip->SetVelo(m_Velocity.x, 0, 0);
						SceneManager::m_SoundManager.Play(SOUND_LABEL_SE007);	// バンドを引っぱる音
						// 第一引数:時間、第二引数:強さ
						Scene::input.SetVibration(30, 10 * bandTip->pullLeveL);
					}
				}
			}
			else
			{
				bandTip->isGrabing = false;
				bandTip->SetPullLeveL(0);
			}
		}
	}
	else
	{
		grabState = DEFAULT;
	}

	if (Scene::input.GetKeyRelease(VK_E) || 
	  ((Scene::input.GetLeftTrigger() <= 0.1 && 
	    Scene::input.GetLeftTrigger() > 0 ) ||
	  ((Scene::input.GetRightTrigger() <= 0.1 &&
	    Scene::input.GetRightTrigger() > 0))))
	{
		auto allBand = Scene::GetInstance()->GetObjects<BandTip>();
		for (auto& band : allBand)
		{
			band->isGrabing = false;
		}
	}

	if (m_Velocity.LengthSquared() > 0.000001f)
	{
		groundState = MOVE;
	}
	else
	{
		groundState = STOP;
	}
}

//===================================================================
// プレイヤーの左右移動処理
//===================================================================
void Player::Walk() {
	if (Scene::input.GetKeyPress(VK_D) || 
	   (Scene::input.GetLeftAnalogStick().x >= 0.7f))
	{
		if (grabState == DEFAULT)
		{
			if (Application::GetFpsCounter() % 10 == 0)
			{
				SceneManager::m_SoundManager.Play(SOUND_LABEL_SE004);	// 足音
				AnimationTex();			// アニメーション更新処理
			}
			moveDirection = RIGHT;
			if (state == ONGROUND)
			{
				m_Velocity.x += velocity;
			}	
			else
			{
				m_Velocity.x += velocity / 1.5f;
			}
			
		}
		else
		{
			if (moveDirection == LEFT)
			{
				m_Velocity.x += velocity / 3.0f;
			}
		}
	}

	if (Scene::input.GetKeyPress(VK_A) ||
	   (Scene::input.GetLeftAnalogStick().x <= -0.7f))
	{
		if (grabState == DEFAULT)
		{
			if (Application::GetFpsCounter() % 10 == 0)
			{
				SceneManager::m_SoundManager.Play(SOUND_LABEL_SE004);	// 足音
				AnimationTex();			// アニメーション更新処理
			}
			moveDirection = LEFT;
			if (state == ONGROUND)
			{
				m_Velocity.x -= velocity;
			}
			else
			{
				m_Velocity.x -= velocity / 1.5f;
			}
		}
		else
		{
			if (moveDirection == RIGHT)
			{
				m_Velocity.x -= velocity / 3.0f;
			}
		}
	}
}

//===================================================================
// プレイヤーのジャンプ処理
//===================================================================
void Player::Jump() {
	if (state == ONGROUND && grabState == DEFAULT)	
	{
		if (Scene::input.GetKeyTrigger(VK_SPACE) ||
			Scene::input.GetButtonTrigger(XINPUT_A))
		{
			SceneManager::m_SoundManager.Play(SOUND_LABEL_SE005);	// ジャンプ音
			m_Velocity.y += jumpSpeed;
		}
	}
}

//===================================================================
// プレイヤーの抵抗処理
//===================================================================
void Player::Resist() {
	m_Velocity /= 1.2f;
}

//===================================================================
// プレイヤーのアニメーション更新処理
//===================================================================
void Player::AnimationTex() {
	auto player = Scene::GetInstance()->GetObjects<Player>();
	for (auto& playerAnim : player)
	{
		if(playerAnim->GetNumU() < 5)
		{
			playerAnim->SetNumU(playerAnim->GetNumU() + 1);
		}
		else if (playerAnim->GetNumU() == 5)
		{
			playerAnim->SetNumU(playerAnim->GetNumU() - 5);
		}
	}
}

std::vector<std::string> Player::GetData() const
{
	std::vector<std::string> buf;
	buf.push_back("Player");
	auto objectData = Object::GetData();
	buf.insert(buf.end(), objectData.begin(), objectData.end());
	return buf;
}

bool Player::SetData(std::vector<std::string> _data)
{
	if (_data.front() == "Player")
	{
		std::vector<std::string> objBuf(_data.size());
		std::copy(_data.begin() + 1, _data.end(), objBuf.begin());
		Object::SetData(objBuf);

		return true;
	}
	else
	{
		return false;
	}
}