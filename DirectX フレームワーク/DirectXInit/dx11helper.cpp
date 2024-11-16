#include <vector>
#include <string>
#include "dx11helper.h"

#pragma comment(lib,"d3dcompiler.lib")

//=============================================================================
// �^�����t�@�C���p�X����t�@�C�����Ɗg���q�𒊏o�E�������ĕԂ�����
//=============================================================================
std::string ExtractFileName(std::string _fullpath, char _split)
{
	// �p�X�̋�؂蕶���̈ʒu��������
	unsigned int path_i = static_cast<unsigned int> (_fullpath.find_last_of(_split) + 1);
	// �g���q�̈ʒu��������
	unsigned int ext_i = static_cast<unsigned int>(_fullpath.find_last_of("."));
	// �p�X�̖��O�𒊏o
	std::string pathname = _fullpath.substr(0, path_i + 1);
	// �t�@�C�����𒊏o
	std::string extname = _fullpath.substr(ext_i, _fullpath.size() - ext_i);
	// �g���q�𒊏o
	std::string filename = _fullpath.substr(path_i, ext_i - path_i);

	// �t�@�C�����Ɗg���q���������ĕԂ�
	return filename + extname;
}

//=============================================================================
// �^������ꂽ�t�@�C��������g���q�𒊏o���ĕԂ�����
//=============================================================================
std::string GetFileExt(const char* _fileName) {
	std::string extName;
	// _fileName��C�������std::string�^�ɕϊ�����
	std::string fullpathstr(_fileName);
	// �g���q�̈ʒu��������
	size_t ext_i = fullpathstr.find_last_of(".");
	// �g���q�𒊏o����
	extName = fullpathstr.substr(ext_i + 1, fullpathstr.size() - ext_i);
	// �g���q��Ԃ�
	return extName;
}

//=============================================================================
// �w�肳�ꂽ�t�@�C��(�V�F�[�_�[�t�@�C��)���o�C�i�����[�h�œǂݍ��݁A���e���o�C�g�z��Ɋi�[���鏈��
//=============================================================================
bool readShader(const char* _csoName, std::vector<unsigned char>& _byteArray)
{
	FILE* fp;
	// �t�@�C�����J��(�grb�h���o�C�i�����[�h)
	int ret = fopen_s(&fp, _csoName, "rb");
	if (ret != 0) {
		return false;
	}
	// �t�@�C���T�C�Y���擾
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	// �o�C�g�z��̃T�C�Y��ݒ肷��
	_byteArray.resize(size);
	// �t�@�C���|�C���^���t�@�C���̐擪�ɖ߂�
	fseek(fp, 0, SEEK_SET);
	// �t�@�C���̓��e��ǂݍ���
	fread(_byteArray.data(), _byteArray.size(), 1, fp);
	// �t�@�C�������
	fclose(fp);
	// ������Ԃ�
	return true;
}

//=============================================================================
// �V�F�[�_�[���t�@�C���̊g���q�ɍ��킹�ăR���p�C�����ĕԂ�����
//=============================================================================
HRESULT CompileShader(const char* _szFileName, LPCSTR _szEntryPoint, LPCSTR _szShaderModel, void** _ShaderObject, size_t& _ShaderObjectSize, ID3DBlob** _ppBlobOut) {

	// ����������
	HRESULT hr;
	static std::vector<unsigned char> byteArray;
	*_ppBlobOut = nullptr;

	// �t�@�C���g���q�̎擾
	std::string extname = GetFileExt(_szFileName);
	// �g���q���gcso�h�̏ꍇ�c
	if (extname == "cso") {
		// �ureadShader�֐��v�Ńt�@�C����ǂݍ���
		bool sts = readShader(_szFileName, byteArray);
		// �ǂݍ��ݎ��s�����ꍇ�A�f�o�b�O�t�@�C���Ƀ��b�Z�[�W���������݁gE_FAIL�h��Ԃ��B
		if (!sts) {
			FILE* fp;
			fopen_s(&fp, "debug.txt", "a");
			fprintf(fp, "file open error \n");
			fclose(fp);
			return E_FAIL;
		}
		*_ShaderObject = byteArray.data();
		_ShaderObjectSize = byteArray.size();
	}
	// �g���q���gcso�h�ȊO�̏ꍇ�c
	else {
		// �uCompileShaderFromFile�֐��v�ŃV�F�[�_�[�t�@�C�����R���p�C������
		hr = CompileShaderFromFile(_szFileName, _szEntryPoint, _szShaderModel, _ppBlobOut);
		// �R���p�C���Ɏ��s�����ꍇ�A"_ppBlobOut"��������A�gE_FAIL�h��Ԃ�
		if (FAILED(hr)) {
			if (*_ppBlobOut)(*_ppBlobOut)->Release();
			return E_FAIL;
		}
		// �R���p�C���ɐ��������ꍇ�A"ShaderObject"�ɃR���p�C�����ʂ̃|�C���^��ݒ�
		*_ShaderObject = (*_ppBlobOut)->GetBufferPointer();
		// ���̐ݒ肵���T�C�Y��ݒ�
		_ShaderObjectSize = (*_ppBlobOut)->GetBufferSize();
	}
	// ������Ԃ�
	return S_OK;
}

//=====================================================================================================================
// �g���q��"cso"�ȊO�̃V�F�[�_�[�t�@�C�����R���p�C�����ĕԂ�����
//=====================================================================================================================
HRESULT CompileShaderFromFile(const char* _szFileName, LPCSTR _szEntryPoint, LPCSTR _szShaderModel, ID3DBlob** _ppBlobOut)
{
	// ����������
	ID3DBlob* p1 = nullptr;
	HRESULT hr = S_OK;
	WCHAR	filename[512];
	size_t 	wLen = 0;
	int err = 0;

	// ���P�[���̐ݒ�
	// �����P�[��:�n��ʁE����ʂɕ�����ꂽ�ݒ����̂���
	setlocale(LC_ALL, "japanese");
	// �t�@�C���̌^����"char�^"���gwchar�^"�ɕϊ�
	err = mbstowcs_s(&wLen, filename, 512, _szFileName, _TRUNCATE);

	// �V�F�[�_�[�R���p�C���̃t���O��ݒ�
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	// �f�o�b�O���[�h�̏ꍇ�gD3DCOMPILE_DEBUG�h�t���O��ǉ�����
#if defined( DEBUG ) || defined( _DEBUG )
	// �gD3DCOMPILE_DEBUG�h�t���O��ݒ肵�ăV�F�[�_�[�t�@�C���Ƀf�o�b�O���𖄂ߍ���
	// �ݒ肷�邱�ƂŃV�F�[�_�[�t�@�C���̃f�o�b�O�����₷���Ȃ邪�A�V�F�[�_�[�͍œK������A
	// �����[�X�\�����Ɠ����悤�ɓ��삷�邱�Ƃ��ۏ؂����
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif
	// ����������
	ID3DBlob* pErrorBlob = nullptr;
	// �V�F�[�_�[�t�@�C���̃R���p�C��
	hr = D3DCompileFromFile(
		filename,							// �t�@�C����			LPCWST pFileName
		nullptr,							// �}�N����`�@			D3D_SHADER_MACRO *pDefines
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	// �C���N���[�h�n���h���@ID3DInclude *pInclude
		_szEntryPoint,						// �G���g���[�|�C���g�@	LPCSTR pEntrypoint
		_szShaderModel,						// �V�F�[�_�[���f���@	LPCSTR pTarget
		dwShaderFlags,						// �R���p�C���t���O�@	UINT Flags1
		0,									// �ǉ��̃t���O�@		UINT Flags2
		_ppBlobOut,							// �R���p�C������		ID3DBlob** ppCode
		&pErrorBlob);						// �G���[���b�Z�[�W		ID3DBlob** ppErrorMsg 
	// �G���[�`�F�b�N
	if (FAILED(hr))
	{
		// �R���p�C�������s�����ꍇ�c
		if (pErrorBlob != nullptr) {
			// �G���[���b�Z�[�W�̕\��
			MessageBox(NULL,
				(char*)pErrorBlob->GetBufferPointer(), "Error", MB_OK);
		}
		//"pErrorBlob"���������
		if (pErrorBlob) pErrorBlob->Release();
		return hr;
	}
	//"pErrorBlob"���������
	if (pErrorBlob) pErrorBlob->Release();

	// ������Ԃ�
	return S_OK;
}


//=================================================================================================
// �w�肳�ꂽ�V�F�[�_�[�t�@�C�����R���p�C���A���_�V�F�[�_�[�Ɠ��̓��C�A�E�g���쐬���鏈��
//=================================================================================================
bool CreateVertexShader(
	ID3D11Device* _device,
	const char* _szFileName,
	LPCSTR _szEntryPoint,
	LPCSTR _szShaderModel,
	D3D11_INPUT_ELEMENT_DESC* _layout,
	unsigned int _numElements,
	ID3D11VertexShader** _ppVertexShader,
	ID3D11InputLayout** _ppVertexLayout) {

	// ����������
	HRESULT hr;
	ID3DBlob* pBlob = nullptr;
	void* ShaderObject;
	size_t	ShaderObjectSize;

	// �uCompileShader�֐��v���Ăяo���A�R���p�C��
	hr = CompileShader(_szFileName, _szEntryPoint, _szShaderModel, &ShaderObject, ShaderObjectSize, &pBlob);
	// �R���p�C�������s�����ꍇ�c
	if (FAILED(hr))
	{
		if (pBlob)pBlob->Release();
		return false;
	}

	// ���_�V�F�[�_�[�̍쐬
	hr = _device->CreateVertexShader(ShaderObject, ShaderObjectSize, nullptr, _ppVertexShader);
	// �쐬�����s�����ꍇ�c
	if (FAILED(hr))
	{
		if (pBlob)pBlob->Release();
		return false;
	}

	// ���̓��C�A�E�g�̍쐬
	hr = _device->CreateInputLayout(
		_layout,
		_numElements,
		ShaderObject,
		ShaderObjectSize,
		_ppVertexLayout);
	// �쐬�����s�����ꍇ�c
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateInputLayout error", "error", MB_OK);
		pBlob->Release();
		return false;
	}

	// ������Ԃ�
	return true;
}

//=================================================================================================
// �w�肳�ꂽ�t�@�C�����R���p�C���A�s�N�Z���V�F�[�_�[���쐬���鏈��
//=================================================================================================
bool CreatePixelShader(ID3D11Device* _device,
	const char* _szFileName,
	LPCSTR _szEntryPoint,
	LPCSTR _szShaderModel,
	ID3D11PixelShader** _ppPixelShader) {

	// ����������
	HRESULT hr;
	ID3DBlob* pBlob = nullptr;
	void* ShaderObject;
	size_t	ShaderObjectSize;

	// �uCompileShader�֐��v���Ăяo���A�R���p�C��
	hr = CompileShader(_szFileName, _szEntryPoint, _szShaderModel, &ShaderObject, ShaderObjectSize, &pBlob);
	// �R���p�C�������s�����ꍇ�c
	if (FAILED(hr))
	{
		return false;
	}

	// �s�N�Z���V�F�[�_�[�̍쐬
	hr = _device->CreatePixelShader(ShaderObject, ShaderObjectSize, nullptr, _ppPixelShader);
	// �쐬�����s�����ꍇ�c
	if (FAILED(hr))
	{
		if (pBlob)pBlob->Release();
		return false;
	}
	// ������Ԃ�
	return true;
}

//=================================================================================================
// �R���X�^���g�o�b�t�@���쐬���鏈��
//=================================================================================================
bool CreateConstantBuffer(
	ID3D11Device* _device,					// �f�o�C�X�I�u�W�F�N�g
	unsigned int _bytesize,					// �R���X�^���g�o�b�t�@�T�C�Y
	ID3D11Buffer** _pConstantBuffer			// �R���X�^���g�o�b�t�@
) {

	// �o�b�t�@�̏�����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	// �o�b�t�@�̐ݒ�
	bd.Usage = D3D11_USAGE_DEFAULT;					// �o�b�t�@�g�p���@(GPU����̓ǂݏ������\�ȃf�t�H���g�ݒ�)
	bd.ByteWidth = _bytesize;						// �o�b�t�@�̃T�C�Y
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		// �R���X�^���g�o�b�t�@�Ƃ��ăo�C���h
	bd.CPUAccessFlags = 0;							// CPU�A�N�Z�X�͕s�v

	// �o�b�t�@�̍쐬
	HRESULT hr = _device->CreateBuffer(&bd, nullptr, _pConstantBuffer);
	// �쐬�����s�����ꍇ�c
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(constant buffer) error", "Error", MB_OK);
		return false;
	}
	// ������Ԃ�
	return true;
}

//=================================================================================================
// CPU�̏������݃A�N�Z�X���\�ȃR���X�^���g�o�b�t�@�̍쐬�����鏈��
//=================================================================================================
bool CreateConstantBufferWrite(
	ID3D11Device* _device,					// �f�o�C�X�I�u�W�F�N�g
	unsigned int _bytesize,					// �R���X�^���g�o�b�t�@�T�C�Y
	ID3D11Buffer** _pConstantBuffer			// �R���X�^���g�o�b�t�@
) {

	// �o�b�t�@�̏�����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	// �o�b�t�@�̐ݒ�
	bd.Usage = D3D11_USAGE_DYNAMIC;					// �o�b�t�@�g�p���@(CPU����̏������݂��\�ȓ��I�o�b�t�@�̐ݒ�)
	bd.ByteWidth = _bytesize;						// �o�b�t�@�̃T�C�Y
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		// �R���X�^���g�o�b�t�@�Ƃ��ăo�C���h
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;		// CPU�A�N�Z�X�\

	// �o�b�t�@�̍쐬
	HRESULT hr = _device->CreateBuffer(&bd, nullptr, _pConstantBuffer);
	// �쐬�����s�����ꍇ�c
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(constant buffer) error", "Error", MB_OK);
		return false;
	}
	// ������Ԃ�
	return true;
}

//=================================================================================================
// �C���f�b�N�X�o�b�t�@�̍쐬�����鏈��
//=================================================================================================
bool CreateIndexBuffer(
	ID3D11Device* _device,						// �f�o�C�X�I�u�W�F�N�g
	unsigned int _indexnum,						// �C���f�b�N�X��
	void* _indexdata,							// �C���f�b�N�X�f�[�^�i�[�������擪�A�h���X
	ID3D11Buffer** _pIndexBuffer) {				// �C���f�b�N�X�o�b�t�@

	// �o�b�t�@�̏�����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	// �o�b�t�@�̐ݒ�
	bd.Usage = D3D11_USAGE_DEFAULT;						// �o�b�t�@�g�p���@(CPU����̓ǂݏ������\�ȃf�t�H���g�ݒ�)
	bd.ByteWidth = sizeof(unsigned int) * _indexnum;	// �o�b�t�@�̃T�C�Y
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;				// �C���f�b�N�X�o�b�t�@�Ƃ��ăo�C���h
	bd.CPUAccessFlags = 0;								// CPU�A�N�Z�X�͕s�v
	
	// �T�u���\�[�X�f�[�^�̏�����
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	// �C���f�b�N�X�f�[�^�̐擪�A�h���X��ݒ�
	InitData.pSysMem = _indexdata;		

	// �o�b�t�@�̍쐬
	HRESULT hr = _device->CreateBuffer(&bd, &InitData, _pIndexBuffer);
	// �쐬�����s�����ꍇ�c
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(index buffer) error", "Error", MB_OK);
		return false;
	}
	// ������Ԃ�
	return true;
}

//=================================================================================================
// ���_�o�b�t�@���쐬���鏈��
//=================================================================================================
bool CreateVertexBuffer(
	ID3D11Device* _device,
	unsigned int _stride,				// �P���_������o�C�g��
	unsigned int _vertexnum,			// ���_��
	void* _vertexdata,					// ���_�f�[�^�i�[�������擪�A�h���X
	ID3D11Buffer** _pVertexBuffer		// ���_�o�b�t�@
) {
	// ����������
	HRESULT hr;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	
	// �o�b�t�@�̐ݒ�
	bd.Usage = D3D11_USAGE_DEFAULT;				// �o�b�t�@�g�p���@(GPU����̓ǂݏ������\�ȃf�t�H���g�ݒ�)
	bd.ByteWidth = _stride * _vertexnum;		// �o�b�t�@�̃T�C�Y
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// ���_�o�b�t�@�Ƃ��ăo�C���h
	bd.CPUAccessFlags = 0;						// CPU�A�N�Z�X�͕s�v

	// �T�u���\�[�X�f�[�^�̏�����
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));

	// ���_�f�[�^�̐擪�A�h���X��ݒ�
	InitData.pSysMem = _vertexdata;		

	// �o�b�t�@�̍쐬
	hr = _device->CreateBuffer(&bd, &InitData, _pVertexBuffer);		
	// �쐬�����s�����ꍇ�c
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(vertex buffer) error", "Error", MB_OK);
		return false;
	}
	// ������Ԃ�
	return true;
}

//=================================================================================================
// CPU�̏������݃A�N�Z�X���\�Ȓ��_�o�b�t�@���쐬���鏈��
//=================================================================================================
bool CreateVertexBufferWrite(
	ID3D11Device* _device,
	unsigned int _stride,				// �P���_������o�C�g��
	unsigned int _vertexnum,			// ���_��
	void* _vertexdata,					// ���_�f�[�^�i�[�������擪�A�h���X
	ID3D11Buffer** _pVertexBuffer		// ���_�o�b�t�@
) {
	// ����������
	HRESULT hr;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	// �o�b�t�@�̐ݒ�
	bd.Usage = D3D11_USAGE_DYNAMIC;							// �o�b�t�@�g�p���@(CPU����̏������݂��\�ȓ��I�o�b�t�@�̐ݒ�)
	bd.ByteWidth = _stride * _vertexnum;					// �o�b�t�@�̃T�C�Y
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;				// ���_�o�b�t�@�Ƃ��ăo�C���h
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;				// CPU�A�N�Z�X���\

	// �T�u���\�[�X�f�[�^�̏�����
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	// ���_�f�[�^�̐擪�A�h���X��ݒ�
	InitData.pSysMem = _vertexdata;		

	// �o�b�t�@�̍쐬
	hr = _device->CreateBuffer(&bd, &InitData, _pVertexBuffer);
	// �쐬�����s�����ꍇ�c
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(vertex buffer) error", "Error", MB_OK);
		return false;
	}
	// ������Ԃ�
	return true;
}

//=================================================================================================
// ���_�o�b�t�@���쐬���A���̃o�b�t�@���V�F�[�_�[���\�[�X�r���[�E�A���I�[�_�[�h�A�N�Z�X�r���[�Ƃ��Ďg�p�ł���悤�ɂ��鏈��
//=================================================================================================
bool CreateVertexBufferUAV(
	ID3D11Device* _device,
	unsigned int _stride,				// �P���_������o�C�g��
	unsigned int _vertexnum,			// ���_��
	void* _vertexdata,					// ���_�f�[�^�i�[�������擪�A�h���X
	ID3D11Buffer** _pVertexBuffer		// ���_�o�b�t�@
) {
	// ������
	HRESULT hr;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	
	// �o�b�t�@�̐ݒ�
	bd.Usage = D3D11_USAGE_DEFAULT;				// �o�b�t�@�̎g�p���@(GPU����̓ǂݏ������\�ȃf�t�H���g�ݒ�)
	bd.ByteWidth = _stride * _vertexnum;		// �o�b�t�@�̃T�C�Y
	bd.BindFlags =
		D3D11_BIND_VERTEX_BUFFER |				// ���_�o�b�t�@�Ƃ��ăo�C���h
		D3D11_BIND_SHADER_RESOURCE |			// �V�F�[�_�[���\�[�X�Ƃ��ăo�C���h
		D3D11_BIND_UNORDERED_ACCESS;			// �A���I�[�_�[�A�N�Z�X�Ƃ��ăo�C���h
	bd.CPUAccessFlags = 0;						// CPU�A�N�Z�X�͕s�v
	// RAW�r���[������
	bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;

	// �T�u���\�[�X�f�[�^�̏�����
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	// ���_�f�[�^�̐擪�A�h���X��ݒ�
	InitData.pSysMem = _vertexdata;		

	// �o�b�t�@�̍쐬
	hr = _device->CreateBuffer(&bd, &InitData, _pVertexBuffer);	
	// �쐬�����s�����ꍇ�c
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(vertex buffer) error", "Error", MB_OK);
		return false;
	}
	// ������Ԃ�
	return true;
}

//=================================================================================================
// �\�����o�b�t�@���쐬���鏈��
//=================================================================================================
bool CreateStructuredBuffer(
	ID3D11Device* _device,
	unsigned int _stride,				// �X�g���C�h�o�C�g��
	unsigned int _num,					// ��
	void* _data,						// �f�[�^�i�[�������擪�A�h���X
	ID3D11Buffer** _pStructuredBuffer	// RWStructuredBuffer
) {
	// ����������
	HRESULT hr;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	// �o�b�t�@�̐ݒ�
	// UA�o�b�t�@�ƃV�F�[�_�[���\�[�X�Ƃ��ăo�C���h
	bd.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;		// UA�o�b�t�@
	// �o�b�t�@�̃T�C�Y
	bd.ByteWidth = _stride * _num;
	// �\�����o�b�t�@�Ƃ��Đݒ�
	bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;							// RWStructuredBuffer
	// �\�����o�b�t�@�̃X�g���C�h
	bd.StructureByteStride = _stride;
	// CPU�A�N�Z�X�͕s�v
	bd.CPUAccessFlags = 0;															// CPU�A�N�Z�X�s�v

	// �T�u���\�[�X�f�[�^�̏�����
	if (_data != nullptr) {
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));

		// �f�[�^�̐擪�A�h���X��ݒ�
		InitData.pSysMem = _data;			
		// �o�b�t�@�̍쐬
		hr = _device->CreateBuffer(&bd, &InitData, _pStructuredBuffer);		
	}
	else {
		// �o�b�t�@�̍쐬
		hr = _device->CreateBuffer(&bd, nullptr, _pStructuredBuffer);	
	}
	// �쐬�����s�����ꍇ�c
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(StructuredBuffer) error", "Error", MB_OK);
		return false;
	}
	// ������Ԃ�
	return true;
}

//=================================================================================================
// �w�肳�ꂽ�o�b�t�@�̓��e���R�s�[���邽�߂̐V�����o�b�t�@���쐬���A�쐬�����o�b�t�@��Ԃ�����
//=================================================================================================
ID3D11Buffer* CreateAndCopyToBuffer(
	ID3D11Device* _device,
	ID3D11DeviceContext* _devicecontext,
	ID3D11Buffer* _pBuffer	// RWStructuredBuffer
) {
	// ������
	HRESULT hr;
	ID3D11Buffer* CloneBuffer = nullptr;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	// ���̃o�b�t�@�̂��擾
	_pBuffer->GetDesc(&bd);

	// �o�b�t�@�̐ݒ�
	// CPU����ǂݎ��\�ɐݒ�
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	// �X�e�[�W���O�o�b�t�@�Ƃ��Ďg�p
	bd.Usage = D3D11_USAGE_STAGING;
	// �o�C���h�t���O���m�F
	bd.BindFlags = 0;
	// ���̑��̃t���O���N���A
	bd.MiscFlags = 0;

	// �V�����o�b�t�@�̍쐬
	hr = _device->CreateBuffer(&bd, nullptr, &CloneBuffer);
	// �쐬�����������ꍇ�c
	if (SUCCEEDED(hr)) {
		// ���̃o�b�t�@�̓��e��V�����쐬�����o�b�t�@�ɃR�s�[����
		_devicecontext->CopyResource(CloneBuffer, _pBuffer);
	}
	// �V�����o�b�t�@��Ԃ�
	return CloneBuffer;
}

//=================================================================================================
// �w�肳�ꂽ�o�b�t�@�̃V�F�[�_�[���\�[�X�r���[(SRV)���쐬���鏈��
//=================================================================================================
bool CreateShaderResourceView(
	ID3D11Device* _device,
	ID3D11Buffer* _pBuffer,	// Buffer
	ID3D11ShaderResourceView** _ppSRV) {

	// �o�b�t�@�̏�����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	// �o�b�t�@�̎擾
	_pBuffer->GetDesc(&bd);

	// �V�F�[�_�[���\�[�X�r���[�̏�����
	D3D11_SHADER_RESOURCE_VIEW_DESC  srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	srvDesc.BufferEx.FirstElement = 0;

	// �o�b�t�@�̎�ނɉ������ݒ�
	// RAW�r���[�������Ă���ꍇ�ARAW�r���[�p�ɐݒ�
	if (bd.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS) {
		srvDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		srvDesc.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
		srvDesc.BufferEx.NumElements = bd.ByteWidth / 4;
	}
	// �o�b�t�@���\�����o�b�t�@�ł���ꍇ�A�\�����o�b�t�@�p�ɐݒ�
	else if (bd.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED) {
		srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		srvDesc.BufferEx.NumElements = bd.ByteWidth / bd.StructureByteStride;
	}
	// ����ȊO�́gfalse�h��Ԃ�
	else {
		return false;
	}

	
	HRESULT hr;
	// �V�F�[�_�[���\�[�X�r���[�̍쐬
	hr = _device->CreateShaderResourceView(_pBuffer, &srvDesc, _ppSRV);
	// �쐬�����s�����ꍇ�c
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateShaderResourceView error", "Error", MB_OK);
		return false;
	}
	// ������Ԃ�
	return true;
}

//=================================================================================================
// �w�肳�ꂽ�o�b�t�@�̃A���I�[�_�[�h�A�N�Z�X�r���[(UAV)���쐬���鏈��
//=================================================================================================
bool CreateUnOrderAccessView(
	ID3D11Device* _device,
	ID3D11Buffer* _pBuffer,	// Buffer
	ID3D11UnorderedAccessView** _ppUAV) {

	// �o�b�t�@�̏�����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	// �o�b�t�@�̎擾
	_pBuffer->GetDesc(&bd);

	// �A���I�[�_�[�h�A�N�Z�X�r���[�̏�����
	D3D11_UNORDERED_ACCESS_VIEW_DESC  uavDesc;
	ZeroMemory(&uavDesc, sizeof(uavDesc));
	uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	uavDesc.Buffer.FirstElement = 0;

	// �o�b�t�@�̎�ނɉ������ݒ�
	// RAW�r���[�������Ă���ꍇ�ARAW�r���[�p�ɐݒ�
	if (bd.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS) {
		uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
		uavDesc.Buffer.NumElements = bd.ByteWidth / 4;
	}
	// �o�b�t�@���\�����o�b�t�@�ł���ꍇ�A�\�����o�b�t�@�p�ɐݒ�
	else if (bd.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED) {
		uavDesc.Format = DXGI_FORMAT_UNKNOWN;
		uavDesc.Buffer.NumElements = bd.ByteWidth / bd.StructureByteStride;
	}
	// ����ȊO���gfalse�h��Ԃ�
	else {
		return false;
	}

	HRESULT hr;
	// �A���I�[�_�[�h�A�N�Z�X�r���[�̍쐬
	hr = _device->CreateUnorderedAccessView(_pBuffer, &uavDesc, _ppUAV);
	// �쐬�����s�����ꍇ�c
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateUnorderedAccessView error", "Error", MB_OK);
		return false;
	}
	// ������Ԃ�
	return true;
}



