#pragma once
#include "Scene.h"

#define OBJECT_X_VALUE		(32)
#define OBJECT_Y_VALUE		(18)
#define GROUND_OFFSET_X		(-930.0f)
#define GROUND_OFFSET_Y		(-510.0f)
#define SCENE_ENUM_OFFSET	(3)

class GameScene : public Scene
{
private:
	int gameSceneNum = 0;	// GameScene(�X�e�[�W)�̎��ʗp�ԍ�
public:
	GameScene(int _num)		//�R���X�g���N�^
	{ Init(_num); };	
	~GameScene() {};		//�f�X�g���N�^

	void Init(int _num);	// ��{�I�ɏ������͂������g��

	//�I�[�o�[���C�h�����֐�
	void Init() {};			// �����������֐�
	void Update();			// �X�V�����֐�
};