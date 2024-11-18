#pragma once

#include "Component.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"

//=======================================================================================
// Quad�N���X
//=======================================================================================
class Quad :public Component 
{
private:
	// �`��̂��߂̏��(���b�V���Ɋւ����)
	IndexBuffer m_IndexBuffer;				// �C���f�b�N�X�o�b�t�@
	VertexBuffer<VERTEX_3D> m_VertexBuffer;	// ���_�o�b�t�@

	// �`��̂��߂̏��(�����ڂɊւ�镔��)
	Shader m_Shader; // �V�F�[�_�[
	Texture m_Texture;	// �e�N�X�`��

public:
	// �I�[�o�[���C�h�����֐�
	void Start(const std::string& filename);	// ����������
	void Update();								// �X�V����
	void Draw();								// �`�揈��
};