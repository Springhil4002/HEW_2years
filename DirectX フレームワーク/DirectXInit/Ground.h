#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Quad.h"
#include "TextureManager.h"

//=======================================================================================
// Ground�N���X
//=======================================================================================
class Ground :public Quad {
public:
	// �I�[�o�[���C�h�����֐�
	void Init();	// ����������
	//void Update();	// �X�V����
	//void Draw();	// �`�揈��
	//void Uninit();	// �������
};