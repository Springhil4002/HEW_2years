#pragma once
#include "Scene.h"

#define OBJECT_X_VALUE		(32)
#define OBJECT_Y_VALUE		(18)
#define GROUND_OFFSET_X		(-930.0f)
#define GROUND_OFFSET_Y		(-510.0f)
#define SCENE_ENUM_OFFSET	(3)

class Goal;
class GameScene : public Scene
{
private:
	int gameSceneNum;			// GameScene(�X�e�[�W)�̎��ʗp�ԍ�
	static int allBandTipCount;	// bandTip�̑���
public:
	static Object* player;
	static int bandTipCount;	// bandTip�̊l����

	GameScene(int _num)			//�R���X�g���N�^
	{ Init(_num); };	
	~GameScene() {};			//�f�X�g���N�^

	void Init(int _num);		// ��{�I�ɏ������͂������g��

	//�I�[�o�[���C�h�����֐�
	void Init() {};				// �����������֐�
	void Update();				// �X�V�����֐�

	// �Q�b�^�[�E�Z�b�^�[
	int GetGameSceneNum() { return gameSceneNum; }
	void SetGameSceneNum(int _gameSceneNum) { gameSceneNum = _gameSceneNum; }

	static int GetAllBandTipCount() { return allBandTipCount; }
	static void SetAllBandTipCount(int _allBandTipCount) { allBandTipCount = _allBandTipCount; }

	void CoinCounter();			// �R�C���l����UI�̊e���X�V����
	void FallIsPlayer();		// player�̗������菈���ƑJ�ڏ���
};