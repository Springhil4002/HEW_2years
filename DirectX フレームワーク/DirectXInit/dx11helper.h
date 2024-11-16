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
	unsigned int stride,				// １頂点当たりバイト数
	unsigned int vertexnum,				// 頂点数
	void* vertexdata,					// 頂点データ格納メモリ先頭アドレス
	ID3D11Buffer** pVertexBuffer		// 頂点バッファ
);

bool CreateVertexBufferWrite(
	ID3D11Device* device,
	unsigned int stride,				// １頂点当たりバイト数
	unsigned int vertexnum,				// 頂点数
	void* vertexdata,					// 頂点データ格納メモリ先頭アドレス
	ID3D11Buffer** pVertexBuffer		// 頂点バッファ
);

bool CreateVertexBufferUAV(
	ID3D11Device* device,
	unsigned int stride,				// １頂点当たりバイト数
	unsigned int vertexnum,				// 頂点数
	void* vertexdata,					// 頂点データ格納メモリ先頭アドレス
	ID3D11Buffer** pVertexBuffer		// 頂点バッファ
);

bool CreateStructuredBuffer(
	ID3D11Device* device,
	unsigned int stride,				// ストライドバイト数
	unsigned int num,					// 個数
	void* data,							// データ格納メモリ先頭アドレス
	ID3D11Buffer** pStructuredBuffer	// StructuredBuffer
);

ID3D11Buffer* CreateAndCopyToBuffer(
	ID3D11Device* device,
	ID3D11DeviceContext* devicecontext,
	ID3D11Buffer* pBuffer	// RWStructuredBuffer
);

bool CreateShaderResourceView(			// バッファからシェーダーリソースビューを作成する	
	ID3D11Device* device,
	ID3D11Buffer* pBuffer,				// Buffer
	ID3D11ShaderResourceView** ppSRV);

bool CreateUnOrderAccessView(
	ID3D11Device* device,
	ID3D11Buffer* pBuffer,				// Buffer
	ID3D11UnorderedAccessView** ppUAV);

bool CreateVertexShader(ID3D11Device* device,		// 頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
	const char* szFileName,
	LPCSTR szEntryPoint,
	LPCSTR szShaderModel,
	D3D11_INPUT_ELEMENT_DESC* layout,
	unsigned int numElements,
	ID3D11VertexShader** ppVertexShader,
	ID3D11InputLayout** ppVertexLayout);


bool CreatePixelShader(ID3D11Device* device,		// ピクセルシェーダーオブジェクトを生成
	const char* szFileName,
	LPCSTR szEntryPoint,
	LPCSTR szShaderModel,
	ID3D11PixelShader** ppPixelShader);

std::string ExtractFileName(std::string fullpath, char split);






