#pragma once

// �O���C���N���[�h
#include	<d3d11.h>
#include	<DirectXMath.h>
#include	<SimpleMath.h>
#include	<io.h>
#include	<string>
#include	<vector>

// �O�����C�u����
#pragma comment(lib,"directxtk.lib")
#pragma comment(lib,"d3d11.lib")

// 3D���_�f�[�^
struct VERTEX_3D
{
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 normal;
	DirectX::SimpleMath::Color	 color;
	DirectX::SimpleMath::Vector2 uv;
};

// �u�����h�X�e�[�g
enum e_BlendState {
	BS_NONE = 0,		// �����������Ȃ�
	BS_ALPHABLEND,		// ����������
	BS_ADDITIVE,		// ���Z����
	BS_SUBTRACTION,		// ���Z����
	MAX_BLENDSTATE		
};

enum e_PROJECTION_TYPE {
	TYPE_2D,
	TYPE_3D
};

// ���s����
struct LIGHT
{
	BOOL Enable;	// �����g�����ۂ��̃t���O
	BOOL Dummy[3];
	DirectX::SimpleMath::Vector4 Direction;	// ���s�����̕���
	DirectX::SimpleMath::Color Diffuse;		// ���s�����̋����ƐF
	DirectX::SimpleMath::Color Ambient;		// �����ɋ����ƐF
};

//=============================================================================
//Renderer�N���X
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

	static ID3D11BlendState*		m_BlendState[MAX_BLENDSTATE];	// �u�����h�X�e�[�g
	static ID3D11BlendState*		m_BlendStateATC;

public:

	static void Init();		// ����������
	static void Uninit();	// �������
	static void Begin();	// �`��J�n����
	static void End();		// �`��I������

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
	// �u�����h�@�X�e�[�g�ݒ�
	//=============================================================================================
	static void SetBlendState(int _nBlendState)
	{
		if (_nBlendState >= 0 && _nBlendState < MAX_BLENDSTATE) {
			float blendFactor[4] = { 0.0f,0.0f,0.0f,0.0f };
			m_DeviceContext->OMSetBlendState(m_BlendState[_nBlendState], blendFactor, 0xffffffff);
		}
	}
};