#pragma once

#include "Entity.h"
#include "TextureManager.h"

//=======================================================================================
// Ground�N���X
//=======================================================================================
class Ground :public Entity {
public:
	// �I�[�o�[���C�h�����֐�
	void Init();	// ����������
	//void Update();	// �X�V����
	//void Draw();	// �`�揈��
	//void Uninit();	// �������

	std::vector<std::string> GetData() const;
	bool SetData(std::vector<std::string> _data);
};