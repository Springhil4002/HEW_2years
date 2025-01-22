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

	int splitX = 1;
	int splitY = 1;
	int numU = 0;
	int numV = 0;
public:
	// �`��ׂ̈̏��i�����ڂɊւ�镔���j
	static Shader m_Shader; // �V�F�[�_�[
	
	Quad() {}
	~Quad() {}

	// �I�[�o�[���C�h�����֐�
	void Init();	// ����������
	void Update();	// �X�V����
	void Draw();	// �`�揈��
	void Uninit();	// �������

	// �摜�ǂݍ���
	// ��������:�摜���A������:���̕������A��O����:�c�̕������A��l����:�����牽�ԖځA��܈���:�c���牽�Ԗ�
	void SetTex(const std::string& filename, 
				int _splitX = 1, int _splitY = 1, 
				int _numU = 0, int _numV = 0);

	// �Q�b�^�[�E�Z�b�^�[

	// splitX�EsplitY�֌W
	int GetSplitX() { return splitX; }
	int GetSplitY() { return splitY; }
	void SetSplitX(int _splitX) { splitX = _splitX; }
	void SetSplitY(int _splitY) { splitY = _splitY; }

	// numU�EnumV�֌W
	int GetNumU() { return numU; }
	int GetNumV() { return numV; }
	void SetNumU(int _numU) { numU = _numU; }
	void SetNumV(int _numV) { numV = _numV; }

	std::vector<std::string> GetData() const;
	bool SetData(std::vector<std::string> _data);
};