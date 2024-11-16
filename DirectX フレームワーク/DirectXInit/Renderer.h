#pragma once

// 外部インクルード
#include	<d3d11.h>
#include	<DirectXMath.h>
#include	<SimpleMath.h>
#include	<io.h>
#include	<string>
#include	<vector>

// 外部ライブラリ
#pragma comment(lib,"directxtk.lib")
#pragma comment(lib,"d3d11.lib")

// 3D頂点データ
struct VERTEX_3D
{
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 normal;
	DirectX::SimpleMath::Color	 color;
	DirectX::SimpleMath::Vector2 uv;
};

// ブレンドステート
enum e_BlendState {
	BS_NONE = 0,		// 半透明合成なし
	BS_ALPHABLEND,		// 半透明合成
	BS_ADDITIVE,		// 加算合成
	BS_SUBTRACTION,		// 減算合成
	MAX_BLENDSTATE		
};

enum e_PROJECTION_TYPE {
	TYPE_2D,
	TYPE_3D
};

// 平行光源
struct LIGHT
{
	BOOL Enable;	// 光を使うか否かのフラグ
	BOOL Dummy[3];
	DirectX::SimpleMath::Vector4 Direction;	// 平行光源の方向
	DirectX::SimpleMath::Color Diffuse;		// 平行光源の強さと色
	DirectX::SimpleMath::Color Ambient;		// 環境光に強さと色
};

//=============================================================================
//Rendererクラス
//=============================================================================
class Renderer
{
private:

	static D3D_FEATURE_LEVEL		m_FeatureLevel;

	static ID3D11Device*			m_Device;
	static ID3D11DeviceContext*		m_DeviceContext;
	static IDXGISwapChain*			m_SwapChain;
	static ID3D11RenderTargetView*	m_RenderTargetView;
	static ID3D11DepthStencilView*	m_DepthStencilView;
 
	static ID3D11Buffer*			m_WorldBuffer;
	static ID3D11Buffer*			m_ViewBuffer;
	static ID3D11Buffer*			m_ProjectionBuffer;

	static ID3D11Buffer*			m_LightBuffer;

	static ID3D11DepthStencilState* m_DepthStateEnable;
	static ID3D11DepthStencilState* m_DepthStateDisable;

	static ID3D11BlendState*		m_BlendState[MAX_BLENDSTATE];	// ブレンドステート
	static ID3D11BlendState*		m_BlendStateATC;

public:

	static void Init();		// 初期化処理
	static void Uninit();	// 解放処理
	static void Begin();	// 描画開始処理
	static void End();		// 描画終了処理

	static void SetDepthEnable(bool _Enable);
	static void SetATCEnable  (bool _Enable);

	static void SetWorldViewProjection2D();	
	static void SetWorldMatrix(DirectX::SimpleMath::Matrix* _WorldMatrix);
	static void SetViewMatrix (DirectX::SimpleMath::Matrix* _ViewMatrix);
	static void SetProjectionMatrix(DirectX::SimpleMath::Matrix* _ProjectionMatrix);

	static ID3D11Device* GetDevice(void) { return m_Device; }
	static ID3D11DeviceContext* GetDeviceContext(void) { return m_DeviceContext; }

	static void CreateVertexShader(ID3D11VertexShader** _VertexShader, ID3D11InputLayout** _VertexLayout, const char* _FileName);
	static void CreatePixelShader(ID3D11PixelShader** _PixelShader, const char* _FiliName);

	static void SetLight(LIGHT _Light);

	//=============================================================================================
	// ブレンド　ステート設定
	//=============================================================================================
	static void SetBlendState(int _nBlendState)
	{
		if (_nBlendState >= 0 && _nBlendState < MAX_BLENDSTATE) {
			float blendFactor[4] = { 0.0f,0.0f,0.0f,0.0f };
			m_DeviceContext->OMSetBlendState(m_BlendState[_nBlendState], blendFactor, 0xffffffff);
		}
	}
};