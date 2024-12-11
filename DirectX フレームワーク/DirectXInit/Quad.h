#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Object.h"
#include "TextureManager.h"

//=======================================================================================
// Quad�N���X
//=======================================================================================
class Quad :public Object{
protected:
	enum MOVEDIRECTION {
		LEFT,
		RIGHT
	};
	// �`��̂��߂̏��(���b�V���Ɋւ����)
	IndexBuffer m_IndexBuffer;				// �C���f�b�N�X�o�b�t�@
	VertexBuffer<VERTEX_3D> m_VertexBuffer;	// ���_�o�b�t�@

	// �`��̂��߂̏��(�����ڂɊւ�镔��)
	TextureManager m_Texture;	// �e�N�X�`��

	MOVEDIRECTION moveDirection = RIGHT;

private:
	MOVEDIRECTION old = moveDirection;

public:
	// �`��ׂ̈̏��i�����ڂɊւ�镔���j
	static Shader m_Shader; // �V�F�[�_�[

	// �I�[�o�[���C�h�����֐�
	void Init();	// ����������
	void Update();	// �X�V����
	void Draw();	// �`�揈��
	void Uninit();	// �������

	void SetTex(const std::string& filename);
};