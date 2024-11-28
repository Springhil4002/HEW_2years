#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Object.h"
#include "TextureManager.h"

//=======================================================================================
// Quad�N���X
//=======================================================================================
class Quad :public Object{
protected:
	// �`��̂��߂̏��(���b�V���Ɋւ����)
	IndexBuffer m_IndexBuffer;				// �C���f�b�N�X�o�b�t�@
	VertexBuffer<VERTEX_3D> m_VertexBuffer;	// ���_�o�b�t�@

	// �`��̂��߂̏��(�����ڂɊւ�镔��)
	TextureManager m_Texture;	// �e�N�X�`��

public:

	void Init(const std::string& filename);
	// �I�[�o�[���C�h�����֐�
	void Update();	// �X�V����
	void Draw();	// �`�揈��
	void Uninit();	// �������
};