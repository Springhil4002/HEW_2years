#include <vector>
#include <string>
#include "dx11helper.h"

#pragma comment(lib,"d3dcompiler.lib")

//=============================================================================
// 与えたファイルパスからファイル名と拡張子を抽出・結合して返す処理
//=============================================================================
std::string ExtractFileName(std::string _fullpath, char _split)
{
	// パスの区切り文字の位置を見つける
	unsigned int path_i = static_cast<unsigned int> (_fullpath.find_last_of(_split) + 1);
	// 拡張子の位置を見つける
	unsigned int ext_i = static_cast<unsigned int>(_fullpath.find_last_of("."));
	// パスの名前を抽出
	std::string pathname = _fullpath.substr(0, path_i + 1);
	// ファイル名を抽出
	std::string extname = _fullpath.substr(ext_i, _fullpath.size() - ext_i);
	// 拡張子を抽出
	std::string filename = _fullpath.substr(path_i, ext_i - path_i);

	// ファイル名と拡張子を結合して返す
	return filename + extname;
}

//=============================================================================
// 与えたられたファイル名から拡張子を抽出して返す処理
//=============================================================================
std::string GetFileExt(const char* _fileName) {
	std::string extName;
	// _fileNameのC文字列をstd::string型に変換する
	std::string fullpathstr(_fileName);
	// 拡張子の位置を見つける
	size_t ext_i = fullpathstr.find_last_of(".");
	// 拡張子を抽出する
	extName = fullpathstr.substr(ext_i + 1, fullpathstr.size() - ext_i);
	// 拡張子を返す
	return extName;
}

//=============================================================================
// 指定されたファイル(シェーダーファイル)をバイナリモードで読み込み、内容をバイト配列に格納する処理
//=============================================================================
bool readShader(const char* _csoName, std::vector<unsigned char>& _byteArray)
{
	FILE* fp;
	// ファイルを開く(“rb”がバイナリモード)
	int ret = fopen_s(&fp, _csoName, "rb");
	if (ret != 0) {
		return false;
	}
	// ファイルサイズを取得
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	// バイト配列のサイズを設定する
	_byteArray.resize(size);
	// ファイルポインタをファイルの先頭に戻す
	fseek(fp, 0, SEEK_SET);
	// ファイルの内容を読み込む
	fread(_byteArray.data(), _byteArray.size(), 1, fp);
	// ファイルを閉じる
	fclose(fp);
	// 成功を返す
	return true;
}

//=============================================================================
// シェーダーをファイルの拡張子に合わせてコンパイルして返す処理
//=============================================================================
HRESULT CompileShader(const char* _szFileName, LPCSTR _szEntryPoint, LPCSTR _szShaderModel, void** _ShaderObject, size_t& _ShaderObjectSize, ID3DBlob** _ppBlobOut) {

	// 初期化処理
	HRESULT hr;
	static std::vector<unsigned char> byteArray;
	*_ppBlobOut = nullptr;

	// ファイル拡張子の取得
	std::string extname = GetFileExt(_szFileName);
	// 拡張子が“cso”の場合…
	if (extname == "cso") {
		// 「readShader関数」でファイルを読み込む
		bool sts = readShader(_szFileName, byteArray);
		// 読み込み失敗した場合、デバッグファイルにメッセージを書きこみ“E_FAIL”を返す。
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
	// 拡張子が“cso”以外の場合…
	else {
		// 「CompileShaderFromFile関数」でシェーダーファイルをコンパイルする
		hr = CompileShaderFromFile(_szFileName, _szEntryPoint, _szShaderModel, _ppBlobOut);
		// コンパイルに失敗した場合、"_ppBlobOut"を解放し、“E_FAIL”を返す
		if (FAILED(hr)) {
			if (*_ppBlobOut)(*_ppBlobOut)->Release();
			return E_FAIL;
		}
		// コンパイルに成功した場合、"ShaderObject"にコンパイル結果のポインタを設定
		*_ShaderObject = (*_ppBlobOut)->GetBufferPointer();
		// ↑の設定したサイズを設定
		_ShaderObjectSize = (*_ppBlobOut)->GetBufferSize();
	}
	// 成功を返す
	return S_OK;
}

//=====================================================================================================================
// 拡張子が"cso"以外のシェーダーファイルをコンパイルして返す処理
//=====================================================================================================================
HRESULT CompileShaderFromFile(const char* _szFileName, LPCSTR _szEntryPoint, LPCSTR _szShaderModel, ID3DBlob** _ppBlobOut)
{
	// 初期化処理
	ID3DBlob* p1 = nullptr;
	HRESULT hr = S_OK;
	WCHAR	filename[512];
	size_t 	wLen = 0;
	int err = 0;

	// ロケールの設定
	// ※ロケール:地域別・言語別に分けられた設定や情報のこと
	setlocale(LC_ALL, "japanese");
	// ファイルの型名を"char型"→“wchar型"に変換
	err = mbstowcs_s(&wLen, filename, 512, _szFileName, _TRUNCATE);

	// シェーダーコンパイルのフラグを設定
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	// デバッグモードの場合“D3DCOMPILE_DEBUG”フラグを追加する
#if defined( DEBUG ) || defined( _DEBUG )
	// “D3DCOMPILE_DEBUG”フラグを設定してシェーダーファイルにデバッグ情報を埋め込む
	// 設定することでシェーダーファイルのデバッグがしやすくなるが、シェーダーは最適化され、
	// リリース構成時と同じように動作することが保証される
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif
	// 初期化処理
	ID3DBlob* pErrorBlob = nullptr;
	// シェーダーファイルのコンパイル
	hr = D3DCompileFromFile(
		filename,							// ファイル名			LPCWST pFileName
		nullptr,							// マクロ定義　			D3D_SHADER_MACRO *pDefines
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	// インクルードハンドラ　ID3DInclude *pInclude
		_szEntryPoint,						// エントリーポイント　	LPCSTR pEntrypoint
		_szShaderModel,						// シェーダーモデル　	LPCSTR pTarget
		dwShaderFlags,						// コンパイルフラグ　	UINT Flags1
		0,									// 追加のフラグ　		UINT Flags2
		_ppBlobOut,							// コンパイル結果		ID3DBlob** ppCode
		&pErrorBlob);						// エラーメッセージ		ID3DBlob** ppErrorMsg 
	// エラーチェック
	if (FAILED(hr))
	{
		// コンパイルが失敗した場合…
		if (pErrorBlob != nullptr) {
			// エラーメッセージの表示
			MessageBox(NULL,
				(char*)pErrorBlob->GetBufferPointer(), "Error", MB_OK);
		}
		//"pErrorBlob"を解放する
		if (pErrorBlob) pErrorBlob->Release();
		return hr;
	}
	//"pErrorBlob"を解放する
	if (pErrorBlob) pErrorBlob->Release();

	// 成功を返す
	return S_OK;
}


//=================================================================================================
// 指定されたシェーダーファイルをコンパイル、頂点シェーダーと入力レイアウトを作成する処理
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

	// 初期化処理
	HRESULT hr;
	ID3DBlob* pBlob = nullptr;
	void* ShaderObject;
	size_t	ShaderObjectSize;

	// 「CompileShader関数」を呼び出し、コンパイル
	hr = CompileShader(_szFileName, _szEntryPoint, _szShaderModel, &ShaderObject, ShaderObjectSize, &pBlob);
	// コンパイルが失敗した場合…
	if (FAILED(hr))
	{
		if (pBlob)pBlob->Release();
		return false;
	}

	// 頂点シェーダーの作成
	hr = _device->CreateVertexShader(ShaderObject, ShaderObjectSize, nullptr, _ppVertexShader);
	// 作成が失敗した場合…
	if (FAILED(hr))
	{
		if (pBlob)pBlob->Release();
		return false;
	}

	// 入力レイアウトの作成
	hr = _device->CreateInputLayout(
		_layout,
		_numElements,
		ShaderObject,
		ShaderObjectSize,
		_ppVertexLayout);
	// 作成が失敗した場合…
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateInputLayout error", "error", MB_OK);
		pBlob->Release();
		return false;
	}

	// 成功を返す
	return true;
}

//=================================================================================================
// 指定されたファイルをコンパイル、ピクセルシェーダーを作成する処理
//=================================================================================================
bool CreatePixelShader(ID3D11Device* _device,
	const char* _szFileName,
	LPCSTR _szEntryPoint,
	LPCSTR _szShaderModel,
	ID3D11PixelShader** _ppPixelShader) {

	// 初期化処理
	HRESULT hr;
	ID3DBlob* pBlob = nullptr;
	void* ShaderObject;
	size_t	ShaderObjectSize;

	// 「CompileShader関数」を呼び出し、コンパイル
	hr = CompileShader(_szFileName, _szEntryPoint, _szShaderModel, &ShaderObject, ShaderObjectSize, &pBlob);
	// コンパイルが失敗した場合…
	if (FAILED(hr))
	{
		return false;
	}

	// ピクセルシェーダーの作成
	hr = _device->CreatePixelShader(ShaderObject, ShaderObjectSize, nullptr, _ppPixelShader);
	// 作成が失敗した場合…
	if (FAILED(hr))
	{
		if (pBlob)pBlob->Release();
		return false;
	}
	// 成功を返す
	return true;
}

//=================================================================================================
// コンスタントバッファを作成する処理
//=================================================================================================
bool CreateConstantBuffer(
	ID3D11Device* _device,					// デバイスオブジェクト
	unsigned int _bytesize,					// コンスタントバッファサイズ
	ID3D11Buffer** _pConstantBuffer			// コンスタントバッファ
) {

	// バッファの初期化
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	// バッファの設定
	bd.Usage = D3D11_USAGE_DEFAULT;					// バッファ使用方法(GPUからの読み書きが可能なデフォルト設定)
	bd.ByteWidth = _bytesize;						// バッファのサイズ
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		// コンスタントバッファとしてバインド
	bd.CPUAccessFlags = 0;							// CPUアクセスは不要

	// バッファの作成
	HRESULT hr = _device->CreateBuffer(&bd, nullptr, _pConstantBuffer);
	// 作成が失敗した場合…
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(constant buffer) error", "Error", MB_OK);
		return false;
	}
	// 成功を返す
	return true;
}

//=================================================================================================
// CPUの書きこみアクセスが可能なコンスタントバッファの作成をする処理
//=================================================================================================
bool CreateConstantBufferWrite(
	ID3D11Device* _device,					// デバイスオブジェクト
	unsigned int _bytesize,					// コンスタントバッファサイズ
	ID3D11Buffer** _pConstantBuffer			// コンスタントバッファ
) {

	// バッファの初期化
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	// バッファの設定
	bd.Usage = D3D11_USAGE_DYNAMIC;					// バッファ使用方法(CPUからの書き込みが可能な動的バッファの設定)
	bd.ByteWidth = _bytesize;						// バッファのサイズ
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		// コンスタントバッファとしてバインド
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;		// CPUアクセス可能

	// バッファの作成
	HRESULT hr = _device->CreateBuffer(&bd, nullptr, _pConstantBuffer);
	// 作成が失敗した場合…
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(constant buffer) error", "Error", MB_OK);
		return false;
	}
	// 成功を返す
	return true;
}

//=================================================================================================
// インデックスバッファの作成をする処理
//=================================================================================================
bool CreateIndexBuffer(
	ID3D11Device* _device,						// デバイスオブジェクト
	unsigned int _indexnum,						// インデックス数
	void* _indexdata,							// インデックスデータ格納メモリ先頭アドレス
	ID3D11Buffer** _pIndexBuffer) {				// インデックスバッファ

	// バッファの初期化
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	// バッファの設定
	bd.Usage = D3D11_USAGE_DEFAULT;						// バッファ使用方法(CPUからの読み書きが可能なデフォルト設定)
	bd.ByteWidth = sizeof(unsigned int) * _indexnum;	// バッファのサイズ
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;				// インデックスバッファとしてバインド
	bd.CPUAccessFlags = 0;								// CPUアクセスは不要
	
	// サブリソースデータの初期化
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	// インデックスデータの先頭アドレスを設定
	InitData.pSysMem = _indexdata;		

	// バッファの作成
	HRESULT hr = _device->CreateBuffer(&bd, &InitData, _pIndexBuffer);
	// 作成が失敗した場合…
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(index buffer) error", "Error", MB_OK);
		return false;
	}
	// 成功を返す
	return true;
}

//=================================================================================================
// 頂点バッファを作成する処理
//=================================================================================================
bool CreateVertexBuffer(
	ID3D11Device* _device,
	unsigned int _stride,				// １頂点当たりバイト数
	unsigned int _vertexnum,			// 頂点数
	void* _vertexdata,					// 頂点データ格納メモリ先頭アドレス
	ID3D11Buffer** _pVertexBuffer		// 頂点バッファ
) {
	// 初期化処理
	HRESULT hr;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	
	// バッファの設定
	bd.Usage = D3D11_USAGE_DEFAULT;				// バッファ使用方法(GPUからの読み書きが可能なデフォルト設定)
	bd.ByteWidth = _stride * _vertexnum;		// バッファのサイズ
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// 頂点バッファとしてバインド
	bd.CPUAccessFlags = 0;						// CPUアクセスは不要

	// サブリソースデータの初期化
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));

	// 頂点データの先頭アドレスを設定
	InitData.pSysMem = _vertexdata;		

	// バッファの作成
	hr = _device->CreateBuffer(&bd, &InitData, _pVertexBuffer);		
	// 作成が失敗した場合…
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(vertex buffer) error", "Error", MB_OK);
		return false;
	}
	// 成功を返す
	return true;
}

//=================================================================================================
// CPUの書き込みアクセスが可能な頂点バッファを作成する処理
//=================================================================================================
bool CreateVertexBufferWrite(
	ID3D11Device* _device,
	unsigned int _stride,				// １頂点当たりバイト数
	unsigned int _vertexnum,			// 頂点数
	void* _vertexdata,					// 頂点データ格納メモリ先頭アドレス
	ID3D11Buffer** _pVertexBuffer		// 頂点バッファ
) {
	// 初期化処理
	HRESULT hr;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	// バッファの設定
	bd.Usage = D3D11_USAGE_DYNAMIC;							// バッファ使用方法(CPUからの書き込みが可能な動的バッファの設定)
	bd.ByteWidth = _stride * _vertexnum;					// バッファのサイズ
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;				// 頂点バッファとしてバインド
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;				// CPUアクセスが可能

	// サブリソースデータの初期化
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	// 頂点データの先頭アドレスを設定
	InitData.pSysMem = _vertexdata;		

	// バッファの作成
	hr = _device->CreateBuffer(&bd, &InitData, _pVertexBuffer);
	// 作成が失敗した場合…
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(vertex buffer) error", "Error", MB_OK);
		return false;
	}
	// 成功を返す
	return true;
}

//=================================================================================================
// 頂点バッファを作成し、そのバッファをシェーダーリソースビュー・アンオーダードアクセスビューとして使用できるようにする処理
//=================================================================================================
bool CreateVertexBufferUAV(
	ID3D11Device* _device,
	unsigned int _stride,				// １頂点当たりバイト数
	unsigned int _vertexnum,			// 頂点数
	void* _vertexdata,					// 頂点データ格納メモリ先頭アドレス
	ID3D11Buffer** _pVertexBuffer		// 頂点バッファ
) {
	// 初期化
	HRESULT hr;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	
	// バッファの設定
	bd.Usage = D3D11_USAGE_DEFAULT;				// バッファの使用方法(GPUからの読み書きが可能なデフォルト設定)
	bd.ByteWidth = _stride * _vertexnum;		// バッファのサイズ
	bd.BindFlags =
		D3D11_BIND_VERTEX_BUFFER |				// 頂点バッファとしてバインド
		D3D11_BIND_SHADER_RESOURCE |			// シェーダーリソースとしてバインド
		D3D11_BIND_UNORDERED_ACCESS;			// アンオーダーアクセスとしてバインド
	bd.CPUAccessFlags = 0;						// CPUアクセスは不要
	// RAWビューを許可
	bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;

	// サブリソースデータの初期化
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	// 頂点データの先頭アドレスを設定
	InitData.pSysMem = _vertexdata;		

	// バッファの作成
	hr = _device->CreateBuffer(&bd, &InitData, _pVertexBuffer);	
	// 作成が失敗した場合…
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(vertex buffer) error", "Error", MB_OK);
		return false;
	}
	// 成功を返す
	return true;
}

//=================================================================================================
// 構造化バッファを作成する処理
//=================================================================================================
bool CreateStructuredBuffer(
	ID3D11Device* _device,
	unsigned int _stride,				// ストライドバイト数
	unsigned int _num,					// 個数
	void* _data,						// データ格納メモリ先頭アドレス
	ID3D11Buffer** _pStructuredBuffer	// RWStructuredBuffer
) {
	// 初期化処理
	HRESULT hr;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	// バッファの設定
	// UAバッファとシェーダーリソースとしてバインド
	bd.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;		// UAバッファ
	// バッファのサイズ
	bd.ByteWidth = _stride * _num;
	// 構造化バッファとして設定
	bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;							// RWStructuredBuffer
	// 構造化バッファのストライド
	bd.StructureByteStride = _stride;
	// CPUアクセスは不要
	bd.CPUAccessFlags = 0;															// CPUアクセス不要

	// サブリソースデータの初期化
	if (_data != nullptr) {
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));

		// データの先頭アドレスを設定
		InitData.pSysMem = _data;			
		// バッファの作成
		hr = _device->CreateBuffer(&bd, &InitData, _pStructuredBuffer);		
	}
	else {
		// バッファの作成
		hr = _device->CreateBuffer(&bd, nullptr, _pStructuredBuffer);	
	}
	// 作成が失敗した場合…
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(StructuredBuffer) error", "Error", MB_OK);
		return false;
	}
	// 成功を返す
	return true;
}

//=================================================================================================
// 指定されたバッファの内容をコピーするための新しいバッファを作成し、作成したバッファを返す処理
//=================================================================================================
ID3D11Buffer* CreateAndCopyToBuffer(
	ID3D11Device* _device,
	ID3D11DeviceContext* _devicecontext,
	ID3D11Buffer* _pBuffer	// RWStructuredBuffer
) {
	// 初期化
	HRESULT hr;
	ID3D11Buffer* CloneBuffer = nullptr;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	// 元のバッファのを取得
	_pBuffer->GetDesc(&bd);

	// バッファの設定
	// CPUから読み取り可能に設定
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	// ステージングバッファとして使用
	bd.Usage = D3D11_USAGE_STAGING;
	// バインドフラグを確認
	bd.BindFlags = 0;
	// その他のフラグをクリア
	bd.MiscFlags = 0;

	// 新しいバッファの作成
	hr = _device->CreateBuffer(&bd, nullptr, &CloneBuffer);
	// 作成が成功した場合…
	if (SUCCEEDED(hr)) {
		// 元のバッファの内容を新しく作成したバッファにコピーする
		_devicecontext->CopyResource(CloneBuffer, _pBuffer);
	}
	// 新しいバッファを返す
	return CloneBuffer;
}

//=================================================================================================
// 指定されたバッファのシェーダーリソースビュー(SRV)を作成する処理
//=================================================================================================
bool CreateShaderResourceView(
	ID3D11Device* _device,
	ID3D11Buffer* _pBuffer,	// Buffer
	ID3D11ShaderResourceView** _ppSRV) {

	// バッファの初期化
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	// バッファの取得
	_pBuffer->GetDesc(&bd);

	// シェーダーリソースビューの初期化
	D3D11_SHADER_RESOURCE_VIEW_DESC  srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	srvDesc.BufferEx.FirstElement = 0;

	// バッファの種類に応じた設定
	// RAWビューを許可している場合、RAWビュー用に設定
	if (bd.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS) {
		srvDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		srvDesc.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
		srvDesc.BufferEx.NumElements = bd.ByteWidth / 4;
	}
	// バッファが構造化バッファである場合、構造化バッファ用に設定
	else if (bd.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED) {
		srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		srvDesc.BufferEx.NumElements = bd.ByteWidth / bd.StructureByteStride;
	}
	// それ以外は“false”を返す
	else {
		return false;
	}

	
	HRESULT hr;
	// シェーダーリソースビューの作成
	hr = _device->CreateShaderResourceView(_pBuffer, &srvDesc, _ppSRV);
	// 作成が失敗した場合…
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateShaderResourceView error", "Error", MB_OK);
		return false;
	}
	// 成功を返す
	return true;
}

//=================================================================================================
// 指定されたバッファのアンオーダードアクセスビュー(UAV)を作成する処理
//=================================================================================================
bool CreateUnOrderAccessView(
	ID3D11Device* _device,
	ID3D11Buffer* _pBuffer,	// Buffer
	ID3D11UnorderedAccessView** _ppUAV) {

	// バッファの初期化
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	// バッファの取得
	_pBuffer->GetDesc(&bd);

	// アンオーダードアクセスビューの初期化
	D3D11_UNORDERED_ACCESS_VIEW_DESC  uavDesc;
	ZeroMemory(&uavDesc, sizeof(uavDesc));
	uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	uavDesc.Buffer.FirstElement = 0;

	// バッファの種類に応じた設定
	// RAWビューを許可している場合、RAWビュー用に設定
	if (bd.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS) {
		uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
		uavDesc.Buffer.NumElements = bd.ByteWidth / 4;
	}
	// バッファが構造化バッファである場合、構造化バッファ用に設定
	else if (bd.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED) {
		uavDesc.Format = DXGI_FORMAT_UNKNOWN;
		uavDesc.Buffer.NumElements = bd.ByteWidth / bd.StructureByteStride;
	}
	// それ以外が“false”を返す
	else {
		return false;
	}

	HRESULT hr;
	// アンオーダードアクセスビューの作成
	hr = _device->CreateUnorderedAccessView(_pBuffer, &uavDesc, _ppUAV);
	// 作成が失敗した場合…
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateUnorderedAccessView error", "Error", MB_OK);
		return false;
	}
	// 成功を返す
	return true;
}



