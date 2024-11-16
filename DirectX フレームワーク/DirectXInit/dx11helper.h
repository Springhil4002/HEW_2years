#pragma once
#include <d3dcompiler.h>
#include <directxmath.h>
#include <locale.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <memory>
#include <string>

HRESULT CompileShader(
	const char* _szFileName,
	LPCSTR		_szEntryPoint,
	LPCSTR		_szShaderModel,
	void**		_ShaderObject,
	size_t&		_ShaderObjectsize,
	ID3DBlob**	_ppBlobOut
);

HRESULT CompileShaderFromFile(
	const char* _szFileName,
	LPCSTR		_szEntryPoint,
	LPCSTR		_szShaderModel,
	ID3DBlob** _ppBlobOut
);

bool CreateConstantBuffer(
	ID3D11Device*	_device,
	unsigned int	_bytesize,
	ID3D11Buffer**	_pConstantBuffer
);

bool CreateConstantBufferWrite(
	ID3D11Device*	_device,
	unsigned int	_bytesize,
	ID3D11Buffer**	_pConstantBuffer
);

bool CreateIndexBuffer(
	ID3D11Device*	_device,
	unsigned int	_indexnum,					
	void*			_indexdata,						
	ID3D11Buffer**	_pIndexBuffer
);

bool CreateVertexBuffer(
	ID3D11Device* device,
	unsigned int stride,				// �P���_������o�C�g��
	unsigned int vertexnum,				// ���_��
	void* vertexdata,					// ���_�f�[�^�i�[�������擪�A�h���X
	ID3D11Buffer** pVertexBuffer		// ���_�o�b�t�@
);

bool CreateVertexBufferWrite(
	ID3D11Device* device,
	unsigned int stride,				// �P���_������o�C�g��
	unsigned int vertexnum,				// ���_��
	void* vertexdata,					// ���_�f�[�^�i�[�������擪�A�h���X
	ID3D11Buffer** pVertexBuffer		// ���_�o�b�t�@
);

bool CreateVertexBufferUAV(
	ID3D11Device* device,
	unsigned int stride,				// �P���_������o�C�g��
	unsigned int vertexnum,				// ���_��
	void* vertexdata,					// ���_�f�[�^�i�[�������擪�A�h���X
	ID3D11Buffer** pVertexBuffer		// ���_�o�b�t�@
);

bool CreateStructuredBuffer(
	ID3D11Device* device,
	unsigned int stride,				// �X�g���C�h�o�C�g��
	unsigned int num,					// ��
	void* data,							// �f�[�^�i�[�������擪�A�h���X
	ID3D11Buffer** pStructuredBuffer	// StructuredBuffer
);

ID3D11Buffer* CreateAndCopyToBuffer(
	ID3D11Device* device,
	ID3D11DeviceContext* devicecontext,
	ID3D11Buffer* pBuffer	// RWStructuredBuffer
);

bool CreateShaderResourceView(			// �o�b�t�@����V�F�[�_�[���\�[�X�r���[���쐬����	
	ID3D11Device* device,
	ID3D11Buffer* pBuffer,				// Buffer
	ID3D11ShaderResourceView** ppSRV);

bool CreateUnOrderAccessView(
	ID3D11Device* device,
	ID3D11Buffer* pBuffer,				// Buffer
	ID3D11UnorderedAccessView** ppUAV);

bool CreateVertexShader(ID3D11Device* device,		// ���_�V�F�[�_�[�I�u�W�F�N�g�𐶐��A�����ɒ��_���C�A�E�g������
	const char* szFileName,
	LPCSTR szEntryPoint,
	LPCSTR szShaderModel,
	D3D11_INPUT_ELEMENT_DESC* layout,
	unsigned int numElements,
	ID3D11VertexShader** ppVertexShader,
	ID3D11InputLayout** ppVertexLayout);


bool CreatePixelShader(ID3D11Device* device,		// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g�𐶐�
	const char* szFileName,
	LPCSTR szEntryPoint,
	LPCSTR szShaderModel,
	ID3D11PixelShader** ppPixelShader);

std::string ExtractFileName(std::string fullpath, char split);






