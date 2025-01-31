#pragma once
#include "Scene.h"
#include "Player.h"

#define OBJECT_X_VALUE		(32)
#define OBJECT_Y_VALUE		(18)
#define GROUND_OFFSET_X		(-930.0f)
#define GROUND_OFFSET_Y		(-510.0f)
#define SCENE_ENUM_OFFSET	(3)

class Goal;
class GameScene : public Scene
{
private:
	int gameSceneNum;				// GameScene(�X�e�[�W)�̎��ʗp�ԍ�
	static int allBandTipCount;		// bandTip�̑���
	int countFadeIn = 0;			// �t�F�[�h�C���J�E���g
	int countFadeOut = 0;			// �t�F�[�h�A�E�g�J�E���g
public:
	bool fade_In = true;			// �t�F�[�h�C���t���O
	bool fadeOut_Start = false;		// �t�F�[�h�J�n�t���O
	bool fadeOut_End = false;		// �t�F�[�h�I���t���O
	bool fadeOut_Start_GameOver = false;	// �t�F�[�h�A�E�g�J�n(�Q�[���I�[�o�[)
	bool fadeOut_End_GameOver = false;		// �t�F�[�h�A�E�g�I��(�Q�[���I�[�o�[)
	static int bandTipCount;		// bandTip�̊l����
	static Player* player;

	GameScene(int _num)				//�R���X�g���N�^
	{ Init(_num); };	
	~GameScene() {};				//�f�X�g���N�^

	void Init(int _num);			// ��{�I�ɏ������͂������g��
	void Fade_In();					// �t�F�[�h�C������		(���邭�Ȃ�)
	void Fade_Out();				// �t�F�[�h�A�E�g����	(�Â��Ȃ�)
	void Fade_Out_GameOver();		// �t�F�[�h�A�E�g(�Q�[���I�[�o�[)
	void RetryGame();				// �Q�[�����̃��g���C�@�\

	//�I�[�o�[���C�h�����֐�
	void Init() {};					// �����������֐�
	void Update();					// �X�V�����֐�

	// �Q�b�^�[�E�Z�b�^�[
	int GetGameSceneNum() { return gameSceneNum; }
	void SetGameSceneNum(int _gameSceneNum) { gameSceneNum = _gameSceneNum; }

	static int GetAllBandTipCount() { return allBandTipCount; }
	static void SetAllBandTipCount(int _allBandTipCount) { allBandTipCount = _allBandTipCount; }

	void CoinCounter();			// �R�C���l����UI�̊e���X�V����
	void FallIsPlayer();		// player�̗������菈���ƑJ�ڏ���
};