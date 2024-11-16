#include "Renderer.h"
#include "Application.h"

using namespace DirectX::SimpleMath;

// D3D_FEATURE_LEVELはDirectX3Dのバージョン
D3D_FEATURE_LEVEL Renderer::m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11Device* Renderer::m_Device{};					// Direct3Dデバイス
ID3D11DeviceContext* Renderer::m_DeviceContext{};	// デバイスコンテキスト
IDXGISwapChain* Renderer::m_SwapChain{};			// スワップチェーン
ID3D11RenderTargetView* Renderer::m_RenderTargetView{};	// レンダーターゲットビュー
ID3D11DepthStencilView* Renderer::m_DepthStencilView{};	// デプスステンシルビュー

ID3D11Buffer* Renderer::m_WorldBuffer{};		// ワールド行列
ID3D11Buffer* Renderer::m_ViewBuffer{};			// ビュー行列
ID3D11Buffer* Renderer::m_ProjectionBuffer{};	// プロジェクション行列

ID3D11Buffer* Renderer::m_LightBuffer{};		//　ライト設定(平行光源)

// デプスステンシルステート
ID3D11DepthStencilState* Renderer::m_DepthStateEnable{};
ID3D11DepthStencilState* Renderer::m_DepthStateDisable{};

ID3D11BlendState* Renderer::m_BlendState[MAX_BLENDSTATE];	// ブレンドステート配列
ID3D11BlendState* Renderer::m_BlendStateATC{};				// 特定のアルファテストとカバレッジ(ATC)用のブレンドステート

//=================================================================================================
// 初期化処理
//=================================================================================================
void Renderer::Init()
{
	HRESULT hr = S_OK;

	// デバイス、スワップチェーン作成するための設定
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};	// 初期化処理

	// バックバッファの数を1に設定(ダブルバッファリング)
	swapChainDesc.BufferCount = 1;	

	// バッファの横幅をウィンドウサイズに合わせる
	swapChainDesc.BufferDesc.Width = Application::GetWidth();	

	// バッファの縦幅をウィンドウサイズに合わせる
	swapChainDesc.BufferDesc.Height = Application::GetHeight();		

	// バッファのピクセルフォーマットを設定
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	

	// リフレッシュレートを設定(Hz)
	// ※Numerator:分子、Denominator:分母
	// 1秒間に60回、画面を更新する
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	// バッファの使用用途を設定
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// スワップチェーンのターゲットウィンドウを設定
	swapChainDesc.OutputWindow = Application::GetWindow();		

	// マルチサンプリングの設定(アンチエイリアスのサンプル数とクオリティ)
	swapChainDesc.SampleDesc.Count = 1;		
	swapChainDesc.SampleDesc.Quality = 0;

	// ウィンドウモード(フルスクリーンではなく、ウィンドウモードで実行)
	swapChainDesc.Windowed = TRUE;	

	// デバイスとスワップチェーンの作成
	hr = D3D11CreateDeviceAndSwapChain (
		NULL,D3D_DRIVER_TYPE_HARDWARE,
		NULL,0, 
		NULL,0,
		D3D11_SDK_VERSION,
		&swapChainDesc, 
		&m_SwapChain,
		&m_Device,
		&m_FeatureLevel,
		&m_DeviceContext);
	// ↑の関数呼び出しが失敗してないかifでチェック
	if (FAILED(hr)) return;	

	//　レンダーターゲットビューを作成
	ID3D11Texture2D* renderTarget{};
	hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderTarget);
	if (renderTarget != nullptr)m_Device->CreateRenderTargetView(renderTarget, NULL, &m_RenderTargetView);
	renderTarget->Release();

	// デプスステンシルバッファを作成するための設定 
	// ※(デプスバッファ = 深度バッファ = Zバッファ)
	// →設定することで奥行を判定して前後関係を正しく描画できる
	ID3D11Texture2D* depthStencile{};						// 初期化処理
	D3D11_TEXTURE2D_DESC textureDesc{};						// 初期化処理
	textureDesc.Width = swapChainDesc.BufferDesc.Width;		// バッファの横幅をスワップチェーンに合わせる
	textureDesc.Height = swapChainDesc.BufferDesc.Height;	// バッファの縦幅をスワップチェーンに合わせる
	textureDesc.MipLevels = 1;								// ミップレベルは1(ミップマップは使用しない)
	textureDesc.ArraySize = 1;								// テクスチャの配列サイズ(通常1)
	textureDesc.Format = DXGI_FORMAT_D16_UNORM;				// フォーマットは16ビットの深度バッファを使用
	textureDesc.SampleDesc = swapChainDesc.SampleDesc;		// スワップチェーンと同じサンプル設定
	textureDesc.Usage = D3D11_USAGE_DEFAULT;				// 使用方法はデフォルト(GPUで使用)
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;		// 深度ステンシルバッファとして使用
	textureDesc.CPUAccessFlags = 0;							// CPUからのアクセスは不要
	textureDesc.MiscFlags = 0;								// その他のフラグを設定なし

	// 新しい2Dテクスチャを作成
	hr = m_Device->CreateTexture2D(&textureDesc, NULL, &depthStencile);
	// ↑の関数呼び出しが失敗してないかifでチェック
	if (FAILED(hr)) return;

	// デプスステンシルビューを作成するための設定
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};	//初期化処理
	// デプスステンシルバッファのフォーマットを設定
	depthStencilViewDesc.Format = textureDesc.Format;	
	// ビューの次元を2Dテクスチャとして設定(2Dテクスチャ用のデプスステンシルビュー)
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;	
	// 特別なフラグは設定しない（デフォルトの動作）
	depthStencilViewDesc.Flags = 0;

	// デプスステンシルビューを作成
	if (depthStencile != nullptr)m_Device->CreateDepthStencilView (
		depthStencile, &depthStencilViewDesc, &m_DepthStencilView);
	depthStencile->Release();	// ポインタが指すリソースの解放(メモリリークを防げる)

	// レンダーターゲットとデプスステンシルビューを設定
	// ※レンダーターゲット:描画先のキャンパス
	// ※デプスステンシルビュー:深度バッファ
	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

	// ビューポートを作成するための設定
	// (画面分割などに使う、描画領域の指定のこと）
	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)Application::GetWidth();	// ビューポートの横幅	
	viewport.Height = (FLOAT)Application::GetHeight();	// ビューポートの縦幅
	viewport.MinDepth = 0.0f;							// 深度範囲の最小値
	viewport.MaxDepth = 1.0f;							// 深度範囲の最大値
	viewport.TopLeftX = 0;								// ビューポートの左上隅のX座標
	viewport.TopLeftY = 0;								// ビューポートの左上隅のY座標

	// デバイスコンテキストにビューポートの数と設定情報を格納したポインタを渡す
	m_DeviceContext->RSSetViewports(1, &viewport);		

	// ラスタライザステートを作るための設定
	D3D11_RASTERIZER_DESC rasterizarDesc{};
	
	// 塗りつぶしモードを(実線)に設定。ポリゴンを塗りつぶして描画するモード
	rasterizarDesc.FillMode = D3D11_FILL_SOLID;

	// 塗りつぶしモードを(ワイヤーフレーム)に設定。ポリゴンのエッジのみを描画するモード
	// rasterizarDesc.FillMode = D3D11_FILL_WIREFRAME;
	
	// カリングモードをバックフェースカリングに設定。カメラから見えない裏側のポリゴンを描画しない設定
	rasterizarDesc.CullMode = D3D11_CULL_BACK;

	// カリングモードをを無効に設定。全てのポリゴンを描画する
	// rasterizarDesc.CullMode = D3D11_CULL_NONE;
	
	// カリングモードをフロントフェースカリングに設定。カメラから見える表側のポリゴンを描画しない設定 
	// rasterizarDesc.CullMode = D3D11_CULL_FRONT;
	
	// デプスクリップを有効に設定。これにより近クリップ間及び、遠クリップ面の外側にあるポリゴンが描画されなくなる設定
	rasterizarDesc.DepthClipEnable = TRUE;
	
	// マルチサンプリングを無効に設定。アンチエイリアスが無効になる設定。
	rasterizarDesc.MultisampleEnable = FALSE;

	// ラスタライザステートの変数宣言
	ID3D11RasterizerState* rs;

	// ラスタライザステートの作成
	hr = m_Device->CreateRasterizerState(&rasterizarDesc, &rs);
	// ↑の関数呼び出しが失敗してないかifでチェック
	if (FAILED(hr)) return;
	// デバイスコンテキストに作成したラスタライザステートを設定
	m_DeviceContext->RSSetState(rs);

	// ブレンドステートを作成するための設定
	// (透過処理や加算合成を可能にする色の合成方法)
	D3D11_BLEND_DESC BlendDesc;

	// BlendDesc構造体をゼロで初期化し、メモリをクリア
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));

	// アルファ・トゥ・カバレッジを無効化(透明度をカバレッジとして利用しない)
	BlendDesc.AlphaToCoverageEnable = FALSE;

	// 各レンダーターゲットに対して個別のブレンド設定を有効化。
	BlendDesc.IndependentBlendEnable = TRUE;

	// ブレンドを無効に設定(不透明な描画)
	BlendDesc.RenderTarget[0].BlendEnable = FALSE;

	// ソース(描画するピクセル)のアルファ値を使用
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	
	// デスティネーション(既存のピクセル)の逆アルファ値を使用
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	// ソースとデスティネーションを加算する操作
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	
	// ソースのアルファ値をそのまま使用
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	
	// デスティネーションのアルファ値を無視
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	
	// アルファ値に対して加算操作を行う
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	
	// レンダーターゲットのカラーチャンネル書き込みマスク
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	// ブレンドステートの作成
	hr = m_Device->CreateBlendState(&BlendDesc, &m_BlendState[0]);
	// ↑の関数呼び出しが失敗してないかifでチェック
	if (FAILED(hr)) return;

	// ブレンドステート生成(アルファブレンド用)
	// BlendDesc.AlphaToCoverageEnable=TRUE;
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;	// ブレンドを有効にする設定。ピクセルのブレンドが行われる
	// ブレンドステートの作成
	hr = m_Device->CreateBlendState(&BlendDesc, &m_BlendState[1]);
	// ↑の関数呼び出しが失敗してないかifでチェック
	if (FAILED(hr)) return;

	// ブレンドステート生成(加算合成用)
	// ブレンドの際、ディスティネーションのブレンドファクターを1に設定。
	// ※ディスティネーション=既に書かれているピクセルのこと。
	// 設定することでディスティネーションカラーがそのまま使用される。
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	// ブレンドステートの作成
	hr = m_Device->CreateBlendState(&BlendDesc, &m_BlendState[2]);
	// ↑の関数呼び出しが失敗してないかifでチェック
	if (FAILED(hr)) return;

	// ブレンドステート生成(減算合成用)
	// ブレンド操作をリバースサブトラクト(逆減算)に設定
	//　設定することでソースカラーからディスティネーションカラーを引くことができる
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	// ブレンドステートの作成
	hr = m_Device->CreateBlendState(&BlendDesc, &m_BlendState[3]);
	// ↑の関数呼び出しが失敗してないかifでチェック
	if (FAILED(hr)) return;

	// レンダリングにおける透明度を考慮した描画を有効にするための設定
	// 設定することで透明度の異なるピクセルが正しく合成される
	SetBlendState(BS_ALPHABLEND);

	// デプスステンシルステートを作成するための設定
	D3D11_DEPTH_STENCIL_DESC dsDesc{};	// 初期化処理

	// 深度テストの有効化(ピクセルの深度(Z値)に基づいた描画の有効化)
	// これをすることで近くにあるオブジェクトが遠くにあるオブジェクトを隠すようになる
	dsDesc.DepthEnable = TRUE;
	
	// 深度バッファへの書き込みを全て有効にする
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	
	// 深度比較関数を設定(現在のピクセルの深度値が既存の深度バッファ値
	//				  以下である場合にピクセルを描画する設定)
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	// ステンシルテストを無効にする(ステンシルバッファが使用されなくなる)
	dsDesc.StencilEnable = FALSE;
	
	// 深度有効ステートの作成
	hr = m_Device->CreateDepthStencilState(&dsDesc, &m_DepthStateEnable);
	// ↑の関数呼び出しが失敗してないかifでチェック
	if (FAILED(hr)) return;
	
	// 深度バッファの書き込みを無効にする設定
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	
	// 深度無効ステートの作成
	hr = m_Device->CreateDepthStencilState(&dsDesc, &m_DepthStateDisable);		
	// ↑の関数呼び出しが失敗してないかifでチェック
	if (FAILED(hr)) return;

	// レンダリングパイプラインに深度ステンシルステートを設定
	// 設定することでシーンの深度情報が適切に扱われるようになる
	m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable, NULL);

	// サンプラーステート設定
	// →テクスチャをポリゴンに貼るときに、拡大縮小される際のアルゴリズム
	D3D11_SAMPLER_DESC smpDesc{};	// 初期化処理

	// 異方性フィルタリングを有効にし、テクスチャの画質を良くする
	smpDesc.Filter	 = D3D11_FILTER_ANISOTROPIC;

	// テクスチャのアドレスモードを設定
	// ※D3D11_TEXTURE_ADDRESS_WRAP = テクスチャの座標が1を超えた場合に繰り返し(ラップ)を行う
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	// 異方性フィルタリングの最大サンプリング数を「4」に設定
	smpDesc.MaxAnisotropy = 4;

	// LOD(ディテール)の設定
	// ※D3D11_FLOAT32_MAXは最も詳細なレベル
	smpDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// サンプラーステートの生成
	ID3D11SamplerState* samplerState{};
	hr = m_Device->CreateSamplerState(&smpDesc, &samplerState);
	// ↑の関数呼び出しが失敗してないかifでチェック
	if (FAILED(hr)) return;

	// 定数バッファの作成
	D3D11_BUFFER_DESC bufferDesc{};	//初期化

	// バッファのサイズを設定(バイト単位)
	bufferDesc.ByteWidth = sizeof(Matrix);

	// バッファの使用方法を設定
	// ※D3D11_USAGE_DEFAULT:GPUによって読み取り・書き込みが行われる標準設定
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;

	// バッファのバインドタイプを設定
	// ※D3D11_BIND_CONSTANT_BUFFER:このバッファが定数バッファとして使うことを指す
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// CPUからのアクセス権を設定
	// 0に設定することでCPUからのアクセスを無効にできる
	bufferDesc.CPUAccessFlags = 0;

	// その他のフラグを設定(特別な設定がないので0に設定)
	bufferDesc.MiscFlags = 0;

	// ストライド(バイト単位)を設定
	// ※今回は(浮動小数点数(float)のサイズに設定)
	bufferDesc.StructureByteStride = sizeof(float);

	// 定数バッファの作成(ワールド行列)	
	hr = m_Device->CreateBuffer(&bufferDesc, NULL, &m_WorldBuffer);
	// 作成した定数バッファ(ワールド行列)を頂点シェーダーにバインドする
	m_DeviceContext->VSSetConstantBuffers(0, 1, &m_WorldBuffer);
	// ↑の関数呼び出しが失敗してないかifでチェック
	if (FAILED(hr)) return;

	// 定数バッファの作成(ビュー行列)	
	hr = m_Device->CreateBuffer(&bufferDesc, NULL, &m_ViewBuffer);
	// 作成した定数バッファ(ビュー行列)を頂点シェーダーにバインドする
	m_DeviceContext->VSSetConstantBuffers(1, 1, &m_ViewBuffer);
	// ↑の関数呼び出しが失敗してないかifでチェック
	if (FAILED(hr)) return;

	// 定数バッファの作成(プロジェクション行列)	
	hr = m_Device->CreateBuffer(&bufferDesc, NULL, &m_ProjectionBuffer);
	// 作成した定数バッファ(プロジェクション行列)を頂点シェーダーにバインドする
	m_DeviceContext->VSSetConstantBuffers(2, 1, &m_ProjectionBuffer);
	// ↑の関数呼び出しが失敗してないかifでチェック
	if (FAILED(hr)) return;

	// バッファのサイズを設定(LIGHTのサイズを設定)
	bufferDesc.ByteWidth = sizeof(LIGHT);
	// 定数バッファの作成(ライト情報)
	m_Device->CreateBuffer(&bufferDesc, NULL, &m_LightBuffer);
	// 作成した定数バッファ(ライト情報)を頂点シェーダーにバインドする
	m_DeviceContext->VSSetConstantBuffers(3, 1, &m_LightBuffer);

	// ライトの設定
	LIGHT light{};	// 初期化処理
	
	// ライトの有効化(設定することでライトがシーンに影響を与えるようになる)
	light.Enable = true;
	
	// ライトの方向設定・方向ベクトルの正規化
	light.Direction = Vector4(0.5f, -1.0f, 0.8f, 0.0f);
	light.Direction.Normalize();
	
	// ディフューズカラー(拡散光)の設定
	light.Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
	
	// アンビエントカラー(環境光)の設定
	light.Ambient = Color(0.2f, 0.2f, 0.2f, 1.0f);

	// 設定したライトをシステムにセットする
	// セットすることでシーンのレンダリングに反映される
	SetLight(light);
}

//=============================================================================
// 解放処理
//=============================================================================
void Renderer::Uninit()
{
	m_WorldBuffer->Release();		// 定数バッファ(ワールド行列)の解放処理
	m_ViewBuffer->Release();		// 定数バッファ(ビュー行列)の解放処理
	m_ProjectionBuffer->Release();	// 定数バッファ(プロジェクション行列)の解放処理

	m_LightBuffer->Release();		// 定数バッファ(ライト)の解放処理

	m_DeviceContext->ClearState();	// デバイスコンテキストのすべての設定状態をクリアにする処理
	m_RenderTargetView->Release();	// レンダーターゲットビューの解放処理
	m_SwapChain->Release();			// スワップチェインの解放処理
	m_DeviceContext->Release();		// デバイスコンテキストの解放処理
	m_Device->Release();			// デバイスの解放処理
}

//=============================================================================
// 描画開始処理
//=============================================================================
void Renderer::Begin()
{
	// クリアカラーを設定する配列(何も設定いてなかったら、開くと青色の画面が出てくる)
	float clearColor[4]= { 0.0f,0.0f,1.0f,1.0f };
	// 指定したクリアカラーでレンダーターゲットビュー(描画先)をクリアにする
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, clearColor);
	// 深度ステンシルビューをクリアにする
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

//=============================================================================
// 描画終了処理
//=============================================================================
void Renderer::End()
{
	// フレームを表示するためのもの
	// ※Present():スワップチェーンのバックバッファと
	// フロントバッファを交換して画面に表示する処理
	// 第1引数:垂直同期を有効にしてフレームレートを
	// モニターのリフレッシュレートに合わせる
	// 第2引数:追加オプションを設定する場所、設定なし
	m_SwapChain->Present(1, 0);
}

//=============================================================================
// 深度ステンシルの有効・無効を設定する処理
//=============================================================================
void Renderer::SetDepthEnable(bool _Enable)
{
	if (_Enable)
	{
		// 深度テストを有効にするステンシルステートをセット
		m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable, NULL);
	}
	else
	{
		// 深度テストを無効にするステンシルステートをセット
		m_DeviceContext->OMSetDepthStencilState(m_DepthStateDisable, NULL);
	}
}

//=============================================================================
// アルファテストとカバレッジ(ATC)の有効・無効を設定する処理
//=============================================================================
void Renderer::SetATCEnable(bool _Enable)
{
	// ブレンドファクター(透明度やブレンドの調整に使用)
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	if (_Enable)
	{
		// アルファテストとカバレッジ(ATC)を有効にするブレンドステートをセット
		m_DeviceContext->OMSetBlendState(m_BlendStateATC, blendFactor, 0xffffffff);
	}
	else
	{
		// 通常のブレンドステートをセット
		m_DeviceContext->OMSetBlendState(m_BlendState[0], blendFactor, 0xffffffff);
	}
}

//=============================================================================
// ワールド、ビュー、プロジェクションの初期化、定数バッファに更新する処理
//=============================================================================
void Renderer::SetWorldViewProjection2D()
{
	Matrix world = Matrix::Identity;		// 単位行列に初期化
	world = world.Transpose();				// 行列を転置(行と列を入れ替え)
	// 転置したワールド行列をワールドバッファにアップデート
	m_DeviceContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);

	Matrix view = Matrix::Identity;			// 単位行列に初期化
	view = view.Transpose();				// 行列を転置(行と列を入れ替え)
	// 転置したビュー行列をビューバッファにアップデート
	m_DeviceContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);

	// 2D描画を左上原点にする
	Matrix projection = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f,
		static_cast<float>(Application::GetWidth()),	// ビューボリュームの最小X
		static_cast<float>(Application::GetHeight()),	// ビューボリュームの最小Y
		0.0f,								
		0.0f,
		1.0f);

	projection = projection.Transpose();	// 行列を転置(行と列を入れ替え)
	
	// 転置したプロジェクション行列をプロジェクションバッファにアップデート
	m_DeviceContext->UpdateSubresource(m_ProjectionBuffer, 0, NULL, &projection, 0, 0);
}

//=======================================================================================
// ワールド行列を設定する処理
//=======================================================================================
void Renderer::SetWorldMatrix(Matrix* _WorldMatrix)
{
	Matrix world;
	world = _WorldMatrix->Transpose();		// 転置

	// ワールド行列をGPU側へ送る
	m_DeviceContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);
}

//=======================================================================================
// ビュー行列を設定する処理
//=======================================================================================
void Renderer::SetViewMatrix(Matrix* _ViewMatrix)
{
	Matrix view;
	view = _ViewMatrix->Transpose();		// 転置

	// ビュー行列をGPU側へ送る
	m_DeviceContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);
}

//=======================================================================================
// プロジェクション行列を設定する処理
//=======================================================================================
void Renderer::SetProjectionMatrix(Matrix* _ProjectionMatrix)
{
	Matrix projection;
	projection = _ProjectionMatrix->Transpose();	// 転置

	// プロジェクション行列をGPU側へ送る
	m_DeviceContext->UpdateSubresource(m_ProjectionBuffer, 0, NULL, &projection, 0, 0);
}

//=======================================================================================
// ライトを設定する処理
//=======================================================================================
void Renderer::SetLight(LIGHT _Light)
{
	// ライトの設定をGPU側へ送る
	m_DeviceContext->UpdateSubresource(m_LightBuffer, 0, NULL, &_Light, 0, 0);
}

//=======================================================================================
// 頂点シェーダーを作成する処理
//=======================================================================================
void Renderer::CreateVertexShader(ID3D11VertexShader** _VertexShader, ID3D11InputLayout** _VertexLayout, const char* _FileName)
{
	FILE* file;		// ファイルを開くためのポインタ
	long int fsize;	//ファイルサイズを格納する変数

	// シェーダーファイルをReadBinaryモードで開く
	fopen_s(&file, _FileName, "rb");	
	assert(file);	//ファイルが正常に開けたかどうかを確認

	// ファイルのサイズを取得
	fsize = _filelength(_fileno(file));	
	//ファイルサイズに基づいてバッファを確保
	unsigned char* buffer = new unsigned char[fsize];
	// ファイルからバッファにデータを読み込む
	fread(buffer, fsize, 1, file);
	// 読み込み完了後、ファイルを閉じる
	fclose(file);	

	// デバイスを使って頂点シェーダーを作成
	m_Device->CreateVertexShader(buffer, fsize, NULL, _VertexShader);
	
	// 頂点レイアウト(入力レイアウト)の定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		// 頂点の位置情報（3つのfloat値）
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	0,		D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// 頂点の法線ベクトル情報（3つのfloat値）
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	4 * 3,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// 頂点の色情報（4つのfloat値：RGBA）
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	4 * 6,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// 頂点のテクスチャ座標情報（2つのfloat値）
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0,	4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout); // レイアウトの要素数を取得

	// デバイスを使って頂点レイアウトを作成
	m_Device->CreateInputLayout(layout, numElements, buffer, fsize, _VertexLayout);

	delete[] buffer; // バッファのメモリを解放
}

//=================================================================================================
// ピクセルシェーダーを作成する処理
//=================================================================================================
void Renderer::CreatePixelShader(ID3D11PixelShader** _PixelShader, const char* _FileName)
{
	FILE* file;		// ファイルを開くためのポインタ
	long int fsize;	// ファイルサイズを格納する変数

	// シェーダーファイルをReadBinaryモードで開く
	fopen_s(&file, _FileName, "rb");	
	// ファイルが正常に開けたかどうかを確認
	assert(file);	

	//ファイルサイズを取得
	fsize = _filelength(_fileno(file));	
	// ファイルサイズに基づいてバッファを確認
	unsigned char* buffer = new unsigned char[fsize];	
	// ファイルからバッファにデータを読み込む
	fread(buffer, fsize, 1, file);	
	// 読み込み完了後、ファイルを閉じる
	fclose(file);	

	// デバイスを使ってピクセルシェーダーを作成
	m_Device->CreatePixelShader(buffer, fsize, NULL, _PixelShader);

	delete[] buffer;	//バッファのメモリを解放
}