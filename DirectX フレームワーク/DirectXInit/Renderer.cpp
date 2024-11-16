#include "Renderer.h"
#include "Application.h"

using namespace DirectX::SimpleMath;

// D3D_FEATURE_LEVEL��DirectX3D�̃o�[�W����
D3D_FEATURE_LEVEL Renderer::m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11Device* Renderer::m_Device{};					// Direct3D�f�o�C�X
ID3D11DeviceContext* Renderer::m_DeviceContext{};	// �f�o�C�X�R���e�L�X�g
IDXGISwapChain* Renderer::m_SwapChain{};			// �X���b�v�`�F�[��
ID3D11RenderTargetView* Renderer::m_RenderTargetView{};	// �����_�[�^�[�Q�b�g�r���[
ID3D11DepthStencilView* Renderer::m_DepthStencilView{};	// �f�v�X�X�e���V���r���[

ID3D11Buffer* Renderer::m_WorldBuffer{};		// ���[���h�s��
ID3D11Buffer* Renderer::m_ViewBuffer{};			// �r���[�s��
ID3D11Buffer* Renderer::m_ProjectionBuffer{};	// �v���W�F�N�V�����s��

ID3D11Buffer* Renderer::m_LightBuffer{};		//�@���C�g�ݒ�(���s����)

// �f�v�X�X�e���V���X�e�[�g
ID3D11DepthStencilState* Renderer::m_DepthStateEnable{};
ID3D11DepthStencilState* Renderer::m_DepthStateDisable{};

ID3D11BlendState* Renderer::m_BlendState[MAX_BLENDSTATE];	// �u�����h�X�e�[�g�z��
ID3D11BlendState* Renderer::m_BlendStateATC{};				// ����̃A���t�@�e�X�g�ƃJ�o���b�W(ATC)�p�̃u�����h�X�e�[�g

//=================================================================================================
// ����������
//=================================================================================================
void Renderer::Init()
{
	HRESULT hr = S_OK;

	// �f�o�C�X�A�X���b�v�`�F�[���쐬���邽�߂̐ݒ�
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};	// ����������

	// �o�b�N�o�b�t�@�̐���1�ɐݒ�(�_�u���o�b�t�@�����O)
	swapChainDesc.BufferCount = 1;	

	// �o�b�t�@�̉������E�B���h�E�T�C�Y�ɍ��킹��
	swapChainDesc.BufferDesc.Width = Application::GetWidth();	

	// �o�b�t�@�̏c�����E�B���h�E�T�C�Y�ɍ��킹��
	swapChainDesc.BufferDesc.Height = Application::GetHeight();		

	// �o�b�t�@�̃s�N�Z���t�H�[�}�b�g��ݒ�
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	

	// ���t���b�V�����[�g��ݒ�(Hz)
	// ��Numerator:���q�ADenominator:����
	// 1�b�Ԃ�60��A��ʂ��X�V����
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	// �o�b�t�@�̎g�p�p�r��ݒ�
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// �X���b�v�`�F�[���̃^�[�Q�b�g�E�B���h�E��ݒ�
	swapChainDesc.OutputWindow = Application::GetWindow();		

	// �}���`�T���v�����O�̐ݒ�(�A���`�G�C���A�X�̃T���v�����ƃN�I���e�B)
	swapChainDesc.SampleDesc.Count = 1;		
	swapChainDesc.SampleDesc.Quality = 0;

	// �E�B���h�E���[�h(�t���X�N���[���ł͂Ȃ��A�E�B���h�E���[�h�Ŏ��s)
	swapChainDesc.Windowed = TRUE;	

	// �f�o�C�X�ƃX���b�v�`�F�[���̍쐬
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
	// ���̊֐��Ăяo�������s���ĂȂ���if�Ń`�F�b�N
	if (FAILED(hr)) return;	

	//�@�����_�[�^�[�Q�b�g�r���[���쐬
	ID3D11Texture2D* renderTarget{};
	hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderTarget);
	if (renderTarget != nullptr)m_Device->CreateRenderTargetView(renderTarget, NULL, &m_RenderTargetView);
	renderTarget->Release();

	// �f�v�X�X�e���V���o�b�t�@���쐬���邽�߂̐ݒ� 
	// ��(�f�v�X�o�b�t�@ = �[�x�o�b�t�@ = Z�o�b�t�@)
	// ���ݒ肷�邱�Ƃŉ��s�𔻒肵�đO��֌W�𐳂����`��ł���
	ID3D11Texture2D* depthStencile{};						// ����������
	D3D11_TEXTURE2D_DESC textureDesc{};						// ����������
	textureDesc.Width = swapChainDesc.BufferDesc.Width;		// �o�b�t�@�̉������X���b�v�`�F�[���ɍ��킹��
	textureDesc.Height = swapChainDesc.BufferDesc.Height;	// �o�b�t�@�̏c�����X���b�v�`�F�[���ɍ��킹��
	textureDesc.MipLevels = 1;								// �~�b�v���x����1(�~�b�v�}�b�v�͎g�p���Ȃ�)
	textureDesc.ArraySize = 1;								// �e�N�X�`���̔z��T�C�Y(�ʏ�1)
	textureDesc.Format = DXGI_FORMAT_D16_UNORM;				// �t�H�[�}�b�g��16�r�b�g�̐[�x�o�b�t�@���g�p
	textureDesc.SampleDesc = swapChainDesc.SampleDesc;		// �X���b�v�`�F�[���Ɠ����T���v���ݒ�
	textureDesc.Usage = D3D11_USAGE_DEFAULT;				// �g�p���@�̓f�t�H���g(GPU�Ŏg�p)
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;		// �[�x�X�e���V���o�b�t�@�Ƃ��Ďg�p
	textureDesc.CPUAccessFlags = 0;							// CPU����̃A�N�Z�X�͕s�v
	textureDesc.MiscFlags = 0;								// ���̑��̃t���O��ݒ�Ȃ�

	// �V����2D�e�N�X�`�����쐬
	hr = m_Device->CreateTexture2D(&textureDesc, NULL, &depthStencile);
	// ���̊֐��Ăяo�������s���ĂȂ���if�Ń`�F�b�N
	if (FAILED(hr)) return;

	// �f�v�X�X�e���V���r���[���쐬���邽�߂̐ݒ�
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};	//����������
	// �f�v�X�X�e���V���o�b�t�@�̃t�H�[�}�b�g��ݒ�
	depthStencilViewDesc.Format = textureDesc.Format;	
	// �r���[�̎�����2D�e�N�X�`���Ƃ��Đݒ�(2D�e�N�X�`���p�̃f�v�X�X�e���V���r���[)
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;	
	// ���ʂȃt���O�͐ݒ肵�Ȃ��i�f�t�H���g�̓���j
	depthStencilViewDesc.Flags = 0;

	// �f�v�X�X�e���V���r���[���쐬
	if (depthStencile != nullptr)m_Device->CreateDepthStencilView (
		depthStencile, &depthStencilViewDesc, &m_DepthStencilView);
	depthStencile->Release();	// �|�C���^���w�����\�[�X�̉��(���������[�N��h����)

	// �����_�[�^�[�Q�b�g�ƃf�v�X�X�e���V���r���[��ݒ�
	// �������_�[�^�[�Q�b�g:�`���̃L�����p�X
	// ���f�v�X�X�e���V���r���[:�[�x�o�b�t�@
	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

	// �r���[�|�[�g���쐬���邽�߂̐ݒ�
	// (��ʕ����ȂǂɎg���A�`��̈�̎w��̂��Ɓj
	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)Application::GetWidth();	// �r���[�|�[�g�̉���	
	viewport.Height = (FLOAT)Application::GetHeight();	// �r���[�|�[�g�̏c��
	viewport.MinDepth = 0.0f;							// �[�x�͈͂̍ŏ��l
	viewport.MaxDepth = 1.0f;							// �[�x�͈͂̍ő�l
	viewport.TopLeftX = 0;								// �r���[�|�[�g�̍������X���W
	viewport.TopLeftY = 0;								// �r���[�|�[�g�̍������Y���W

	// �f�o�C�X�R���e�L�X�g�Ƀr���[�|�[�g�̐��Ɛݒ�����i�[�����|�C���^��n��
	m_DeviceContext->RSSetViewports(1, &viewport);		

	// ���X�^���C�U�X�e�[�g����邽�߂̐ݒ�
	D3D11_RASTERIZER_DESC rasterizarDesc{};
	
	// �h��Ԃ����[�h��(����)�ɐݒ�B�|���S����h��Ԃ��ĕ`�悷�郂�[�h
	rasterizarDesc.FillMode = D3D11_FILL_SOLID;

	// �h��Ԃ����[�h��(���C���[�t���[��)�ɐݒ�B�|���S���̃G�b�W�݂̂�`�悷�郂�[�h
	// rasterizarDesc.FillMode = D3D11_FILL_WIREFRAME;
	
	// �J�����O���[�h���o�b�N�t�F�[�X�J�����O�ɐݒ�B�J�������猩���Ȃ������̃|���S����`�悵�Ȃ��ݒ�
	rasterizarDesc.CullMode = D3D11_CULL_BACK;

	// �J�����O���[�h���𖳌��ɐݒ�B�S�Ẵ|���S����`�悷��
	// rasterizarDesc.CullMode = D3D11_CULL_NONE;
	
	// �J�����O���[�h���t�����g�t�F�[�X�J�����O�ɐݒ�B�J�������猩����\���̃|���S����`�悵�Ȃ��ݒ� 
	// rasterizarDesc.CullMode = D3D11_CULL_FRONT;
	
	// �f�v�X�N���b�v��L���ɐݒ�B����ɂ��߃N���b�v�ԋy�сA���N���b�v�ʂ̊O���ɂ���|���S�����`�悳��Ȃ��Ȃ�ݒ�
	rasterizarDesc.DepthClipEnable = TRUE;
	
	// �}���`�T���v�����O�𖳌��ɐݒ�B�A���`�G�C���A�X�������ɂȂ�ݒ�B
	rasterizarDesc.MultisampleEnable = FALSE;

	// ���X�^���C�U�X�e�[�g�̕ϐ��錾
	ID3D11RasterizerState* rs;

	// ���X�^���C�U�X�e�[�g�̍쐬
	hr = m_Device->CreateRasterizerState(&rasterizarDesc, &rs);
	// ���̊֐��Ăяo�������s���ĂȂ���if�Ń`�F�b�N
	if (FAILED(hr)) return;
	// �f�o�C�X�R���e�L�X�g�ɍ쐬�������X�^���C�U�X�e�[�g��ݒ�
	m_DeviceContext->RSSetState(rs);

	// �u�����h�X�e�[�g���쐬���邽�߂̐ݒ�
	// (���ߏ�������Z�������\�ɂ���F�̍������@)
	D3D11_BLEND_DESC BlendDesc;

	// BlendDesc�\���̂��[���ŏ��������A���������N���A
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));

	// �A���t�@�E�g�D�E�J�o���b�W�𖳌���(�����x���J�o���b�W�Ƃ��ė��p���Ȃ�)
	BlendDesc.AlphaToCoverageEnable = FALSE;

	// �e�����_�[�^�[�Q�b�g�ɑ΂��Čʂ̃u�����h�ݒ��L�����B
	BlendDesc.IndependentBlendEnable = TRUE;

	// �u�����h�𖳌��ɐݒ�(�s�����ȕ`��)
	BlendDesc.RenderTarget[0].BlendEnable = FALSE;

	// �\�[�X(�`�悷��s�N�Z��)�̃A���t�@�l���g�p
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	
	// �f�X�e�B�l�[�V����(�����̃s�N�Z��)�̋t�A���t�@�l���g�p
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	// �\�[�X�ƃf�X�e�B�l�[�V���������Z���鑀��
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	
	// �\�[�X�̃A���t�@�l�����̂܂܎g�p
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	
	// �f�X�e�B�l�[�V�����̃A���t�@�l�𖳎�
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	
	// �A���t�@�l�ɑ΂��ĉ��Z������s��
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	
	// �����_�[�^�[�Q�b�g�̃J���[�`�����l���������݃}�X�N
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	// �u�����h�X�e�[�g�̍쐬
	hr = m_Device->CreateBlendState(&BlendDesc, &m_BlendState[0]);
	// ���̊֐��Ăяo�������s���ĂȂ���if�Ń`�F�b�N
	if (FAILED(hr)) return;

	// �u�����h�X�e�[�g����(�A���t�@�u�����h�p)
	// BlendDesc.AlphaToCoverageEnable=TRUE;
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;	// �u�����h��L���ɂ���ݒ�B�s�N�Z���̃u�����h���s����
	// �u�����h�X�e�[�g�̍쐬
	hr = m_Device->CreateBlendState(&BlendDesc, &m_BlendState[1]);
	// ���̊֐��Ăяo�������s���ĂȂ���if�Ń`�F�b�N
	if (FAILED(hr)) return;

	// �u�����h�X�e�[�g����(���Z�����p)
	// �u�����h�̍ہA�f�B�X�e�B�l�[�V�����̃u�����h�t�@�N�^�[��1�ɐݒ�B
	// ���f�B�X�e�B�l�[�V����=���ɏ�����Ă���s�N�Z���̂��ƁB
	// �ݒ肷�邱�ƂŃf�B�X�e�B�l�[�V�����J���[�����̂܂܎g�p�����B
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	// �u�����h�X�e�[�g�̍쐬
	hr = m_Device->CreateBlendState(&BlendDesc, &m_BlendState[2]);
	// ���̊֐��Ăяo�������s���ĂȂ���if�Ń`�F�b�N
	if (FAILED(hr)) return;

	// �u�����h�X�e�[�g����(���Z�����p)
	// �u�����h��������o�[�X�T�u�g���N�g(�t���Z)�ɐݒ�
	//�@�ݒ肷�邱�ƂŃ\�[�X�J���[����f�B�X�e�B�l�[�V�����J���[���������Ƃ��ł���
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	// �u�����h�X�e�[�g�̍쐬
	hr = m_Device->CreateBlendState(&BlendDesc, &m_BlendState[3]);
	// ���̊֐��Ăяo�������s���ĂȂ���if�Ń`�F�b�N
	if (FAILED(hr)) return;

	// �����_�����O�ɂ����铧���x���l�������`���L���ɂ��邽�߂̐ݒ�
	// �ݒ肷�邱�Ƃœ����x�̈قȂ�s�N�Z�������������������
	SetBlendState(BS_ALPHABLEND);

	// �f�v�X�X�e���V���X�e�[�g���쐬���邽�߂̐ݒ�
	D3D11_DEPTH_STENCIL_DESC dsDesc{};	// ����������

	// �[�x�e�X�g�̗L����(�s�N�Z���̐[�x(Z�l)�Ɋ�Â����`��̗L����)
	// ��������邱�Ƃŋ߂��ɂ���I�u�W�F�N�g�������ɂ���I�u�W�F�N�g���B���悤�ɂȂ�
	dsDesc.DepthEnable = TRUE;
	
	// �[�x�o�b�t�@�ւ̏������݂�S�ėL���ɂ���
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	
	// �[�x��r�֐���ݒ�(���݂̃s�N�Z���̐[�x�l�������̐[�x�o�b�t�@�l
	//				  �ȉ��ł���ꍇ�Ƀs�N�Z����`�悷��ݒ�)
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	// �X�e���V���e�X�g�𖳌��ɂ���(�X�e���V���o�b�t�@���g�p����Ȃ��Ȃ�)
	dsDesc.StencilEnable = FALSE;
	
	// �[�x�L���X�e�[�g�̍쐬
	hr = m_Device->CreateDepthStencilState(&dsDesc, &m_DepthStateEnable);
	// ���̊֐��Ăяo�������s���ĂȂ���if�Ń`�F�b�N
	if (FAILED(hr)) return;
	
	// �[�x�o�b�t�@�̏������݂𖳌��ɂ���ݒ�
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	
	// �[�x�����X�e�[�g�̍쐬
	hr = m_Device->CreateDepthStencilState(&dsDesc, &m_DepthStateDisable);		
	// ���̊֐��Ăяo�������s���ĂȂ���if�Ń`�F�b�N
	if (FAILED(hr)) return;

	// �����_�����O�p�C�v���C���ɐ[�x�X�e���V���X�e�[�g��ݒ�
	// �ݒ肷�邱�ƂŃV�[���̐[�x��񂪓K�؂Ɉ�����悤�ɂȂ�
	m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable, NULL);

	// �T���v���[�X�e�[�g�ݒ�
	// ���e�N�X�`�����|���S���ɓ\��Ƃ��ɁA�g��k�������ۂ̃A���S���Y��
	D3D11_SAMPLER_DESC smpDesc{};	// ����������

	// �ٕ����t�B���^�����O��L���ɂ��A�e�N�X�`���̉掿��ǂ�����
	smpDesc.Filter	 = D3D11_FILTER_ANISOTROPIC;

	// �e�N�X�`���̃A�h���X���[�h��ݒ�
	// ��D3D11_TEXTURE_ADDRESS_WRAP = �e�N�X�`���̍��W��1�𒴂����ꍇ�ɌJ��Ԃ�(���b�v)���s��
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	// �ٕ����t�B���^�����O�̍ő�T���v�����O�����u4�v�ɐݒ�
	smpDesc.MaxAnisotropy = 4;

	// LOD(�f�B�e�[��)�̐ݒ�
	// ��D3D11_FLOAT32_MAX�͍ł��ڍׂȃ��x��
	smpDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// �T���v���[�X�e�[�g�̐���
	ID3D11SamplerState* samplerState{};
	hr = m_Device->CreateSamplerState(&smpDesc, &samplerState);
	// ���̊֐��Ăяo�������s���ĂȂ���if�Ń`�F�b�N
	if (FAILED(hr)) return;

	// �萔�o�b�t�@�̍쐬
	D3D11_BUFFER_DESC bufferDesc{};	//������

	// �o�b�t�@�̃T�C�Y��ݒ�(�o�C�g�P��)
	bufferDesc.ByteWidth = sizeof(Matrix);

	// �o�b�t�@�̎g�p���@��ݒ�
	// ��D3D11_USAGE_DEFAULT:GPU�ɂ���ēǂݎ��E�������݂��s����W���ݒ�
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;

	// �o�b�t�@�̃o�C���h�^�C�v��ݒ�
	// ��D3D11_BIND_CONSTANT_BUFFER:���̃o�b�t�@���萔�o�b�t�@�Ƃ��Ďg�����Ƃ��w��
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// CPU����̃A�N�Z�X����ݒ�
	// 0�ɐݒ肷�邱�Ƃ�CPU����̃A�N�Z�X�𖳌��ɂł���
	bufferDesc.CPUAccessFlags = 0;

	// ���̑��̃t���O��ݒ�(���ʂȐݒ肪�Ȃ��̂�0�ɐݒ�)
	bufferDesc.MiscFlags = 0;

	// �X�g���C�h(�o�C�g�P��)��ݒ�
	// �������(���������_��(float)�̃T�C�Y�ɐݒ�)
	bufferDesc.StructureByteStride = sizeof(float);

	// �萔�o�b�t�@�̍쐬(���[���h�s��)	
	hr = m_Device->CreateBuffer(&bufferDesc, NULL, &m_WorldBuffer);
	// �쐬�����萔�o�b�t�@(���[���h�s��)�𒸓_�V�F�[�_�[�Ƀo�C���h����
	m_DeviceContext->VSSetConstantBuffers(0, 1, &m_WorldBuffer);
	// ���̊֐��Ăяo�������s���ĂȂ���if�Ń`�F�b�N
	if (FAILED(hr)) return;

	// �萔�o�b�t�@�̍쐬(�r���[�s��)	
	hr = m_Device->CreateBuffer(&bufferDesc, NULL, &m_ViewBuffer);
	// �쐬�����萔�o�b�t�@(�r���[�s��)�𒸓_�V�F�[�_�[�Ƀo�C���h����
	m_DeviceContext->VSSetConstantBuffers(1, 1, &m_ViewBuffer);
	// ���̊֐��Ăяo�������s���ĂȂ���if�Ń`�F�b�N
	if (FAILED(hr)) return;

	// �萔�o�b�t�@�̍쐬(�v���W�F�N�V�����s��)	
	hr = m_Device->CreateBuffer(&bufferDesc, NULL, &m_ProjectionBuffer);
	// �쐬�����萔�o�b�t�@(�v���W�F�N�V�����s��)�𒸓_�V�F�[�_�[�Ƀo�C���h����
	m_DeviceContext->VSSetConstantBuffers(2, 1, &m_ProjectionBuffer);
	// ���̊֐��Ăяo�������s���ĂȂ���if�Ń`�F�b�N
	if (FAILED(hr)) return;

	// �o�b�t�@�̃T�C�Y��ݒ�(LIGHT�̃T�C�Y��ݒ�)
	bufferDesc.ByteWidth = sizeof(LIGHT);
	// �萔�o�b�t�@�̍쐬(���C�g���)
	m_Device->CreateBuffer(&bufferDesc, NULL, &m_LightBuffer);
	// �쐬�����萔�o�b�t�@(���C�g���)�𒸓_�V�F�[�_�[�Ƀo�C���h����
	m_DeviceContext->VSSetConstantBuffers(3, 1, &m_LightBuffer);

	// ���C�g�̐ݒ�
	LIGHT light{};	// ����������
	
	// ���C�g�̗L����(�ݒ肷�邱�ƂŃ��C�g���V�[���ɉe����^����悤�ɂȂ�)
	light.Enable = true;
	
	// ���C�g�̕����ݒ�E�����x�N�g���̐��K��
	light.Direction = Vector4(0.5f, -1.0f, 0.8f, 0.0f);
	light.Direction.Normalize();
	
	// �f�B�t���[�Y�J���[(�g�U��)�̐ݒ�
	light.Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
	
	// �A���r�G���g�J���[(����)�̐ݒ�
	light.Ambient = Color(0.2f, 0.2f, 0.2f, 1.0f);

	// �ݒ肵�����C�g���V�X�e���ɃZ�b�g����
	// �Z�b�g���邱�ƂŃV�[���̃����_�����O�ɔ��f�����
	SetLight(light);
}

//=============================================================================
// �������
//=============================================================================
void Renderer::Uninit()
{
	m_WorldBuffer->Release();		// �萔�o�b�t�@(���[���h�s��)�̉������
	m_ViewBuffer->Release();		// �萔�o�b�t�@(�r���[�s��)�̉������
	m_ProjectionBuffer->Release();	// �萔�o�b�t�@(�v���W�F�N�V�����s��)�̉������

	m_LightBuffer->Release();		// �萔�o�b�t�@(���C�g)�̉������

	m_DeviceContext->ClearState();	// �f�o�C�X�R���e�L�X�g�̂��ׂĂ̐ݒ��Ԃ��N���A�ɂ��鏈��
	m_RenderTargetView->Release();	// �����_�[�^�[�Q�b�g�r���[�̉������
	m_SwapChain->Release();			// �X���b�v�`�F�C���̉������
	m_DeviceContext->Release();		// �f�o�C�X�R���e�L�X�g�̉������
	m_Device->Release();			// �f�o�C�X�̉������
}

//=============================================================================
// �`��J�n����
//=============================================================================
void Renderer::Begin()
{
	// �N���A�J���[��ݒ肷��z��(�����ݒ肢�ĂȂ�������A�J���ƐF�̉�ʂ��o�Ă���)
	float clearColor[4]= { 0.0f,0.0f,1.0f,1.0f };
	// �w�肵���N���A�J���[�Ń����_�[�^�[�Q�b�g�r���[(�`���)���N���A�ɂ���
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, clearColor);
	// �[�x�X�e���V���r���[���N���A�ɂ���
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

//=============================================================================
// �`��I������
//=============================================================================
void Renderer::End()
{
	// �t���[����\�����邽�߂̂���
	// ��Present():�X���b�v�`�F�[���̃o�b�N�o�b�t�@��
	// �t�����g�o�b�t�@���������ĉ�ʂɕ\�����鏈��
	// ��1����:����������L���ɂ��ăt���[�����[�g��
	// ���j�^�[�̃��t���b�V�����[�g�ɍ��킹��
	// ��2����:�ǉ��I�v�V������ݒ肷��ꏊ�A�ݒ�Ȃ�
	m_SwapChain->Present(1, 0);
}

//=============================================================================
// �[�x�X�e���V���̗L���E������ݒ肷�鏈��
//=============================================================================
void Renderer::SetDepthEnable(bool _Enable)
{
	if (_Enable)
	{
		// �[�x�e�X�g��L���ɂ���X�e���V���X�e�[�g���Z�b�g
		m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable, NULL);
	}
	else
	{
		// �[�x�e�X�g�𖳌��ɂ���X�e���V���X�e�[�g���Z�b�g
		m_DeviceContext->OMSetDepthStencilState(m_DepthStateDisable, NULL);
	}
}

//=============================================================================
// �A���t�@�e�X�g�ƃJ�o���b�W(ATC)�̗L���E������ݒ肷�鏈��
//=============================================================================
void Renderer::SetATCEnable(bool _Enable)
{
	// �u�����h�t�@�N�^�[(�����x��u�����h�̒����Ɏg�p)
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	if (_Enable)
	{
		// �A���t�@�e�X�g�ƃJ�o���b�W(ATC)��L���ɂ���u�����h�X�e�[�g���Z�b�g
		m_DeviceContext->OMSetBlendState(m_BlendStateATC, blendFactor, 0xffffffff);
	}
	else
	{
		// �ʏ�̃u�����h�X�e�[�g���Z�b�g
		m_DeviceContext->OMSetBlendState(m_BlendState[0], blendFactor, 0xffffffff);
	}
}

//=============================================================================
// ���[���h�A�r���[�A�v���W�F�N�V�����̏������A�萔�o�b�t�@�ɍX�V���鏈��
//=============================================================================
void Renderer::SetWorldViewProjection2D()
{
	Matrix world = Matrix::Identity;		// �P�ʍs��ɏ�����
	world = world.Transpose();				// �s���]�u(�s�Ɨ�����ւ�)
	// �]�u�������[���h�s������[���h�o�b�t�@�ɃA�b�v�f�[�g
	m_DeviceContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);

	Matrix view = Matrix::Identity;			// �P�ʍs��ɏ�����
	view = view.Transpose();				// �s���]�u(�s�Ɨ�����ւ�)
	// �]�u�����r���[�s����r���[�o�b�t�@�ɃA�b�v�f�[�g
	m_DeviceContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);

	// 2D�`������㌴�_�ɂ���
	Matrix projection = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f,
		static_cast<float>(Application::GetWidth()),	// �r���[�{�����[���̍ŏ�X
		static_cast<float>(Application::GetHeight()),	// �r���[�{�����[���̍ŏ�Y
		0.0f,								
		0.0f,
		1.0f);

	projection = projection.Transpose();	// �s���]�u(�s�Ɨ�����ւ�)
	
	// �]�u�����v���W�F�N�V�����s����v���W�F�N�V�����o�b�t�@�ɃA�b�v�f�[�g
	m_DeviceContext->UpdateSubresource(m_ProjectionBuffer, 0, NULL, &projection, 0, 0);
}

//=======================================================================================
// ���[���h�s���ݒ肷�鏈��
//=======================================================================================
void Renderer::SetWorldMatrix(Matrix* _WorldMatrix)
{
	Matrix world;
	world = _WorldMatrix->Transpose();		// �]�u

	// ���[���h�s���GPU���֑���
	m_DeviceContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);
}

//=======================================================================================
// �r���[�s���ݒ肷�鏈��
//=======================================================================================
void Renderer::SetViewMatrix(Matrix* _ViewMatrix)
{
	Matrix view;
	view = _ViewMatrix->Transpose();		// �]�u

	// �r���[�s���GPU���֑���
	m_DeviceContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);
}

//=======================================================================================
// �v���W�F�N�V�����s���ݒ肷�鏈��
//=======================================================================================
void Renderer::SetProjectionMatrix(Matrix* _ProjectionMatrix)
{
	Matrix projection;
	projection = _ProjectionMatrix->Transpose();	// �]�u

	// �v���W�F�N�V�����s���GPU���֑���
	m_DeviceContext->UpdateSubresource(m_ProjectionBuffer, 0, NULL, &projection, 0, 0);
}

//=======================================================================================
// ���C�g��ݒ肷�鏈��
//=======================================================================================
void Renderer::SetLight(LIGHT _Light)
{
	// ���C�g�̐ݒ��GPU���֑���
	m_DeviceContext->UpdateSubresource(m_LightBuffer, 0, NULL, &_Light, 0, 0);
}

//=======================================================================================
// ���_�V�F�[�_�[���쐬���鏈��
//=======================================================================================
void Renderer::CreateVertexShader(ID3D11VertexShader** _VertexShader, ID3D11InputLayout** _VertexLayout, const char* _FileName)
{
	FILE* file;		// �t�@�C�����J�����߂̃|�C���^
	long int fsize;	//�t�@�C���T�C�Y���i�[����ϐ�

	// �V�F�[�_�[�t�@�C����ReadBinary���[�h�ŊJ��
	fopen_s(&file, _FileName, "rb");	
	assert(file);	//�t�@�C��������ɊJ�������ǂ������m�F

	// �t�@�C���̃T�C�Y���擾
	fsize = _filelength(_fileno(file));	
	//�t�@�C���T�C�Y�Ɋ�Â��ăo�b�t�@���m��
	unsigned char* buffer = new unsigned char[fsize];
	// �t�@�C������o�b�t�@�Ƀf�[�^��ǂݍ���
	fread(buffer, fsize, 1, file);
	// �ǂݍ��݊�����A�t�@�C�������
	fclose(file);	

	// �f�o�C�X���g���Ē��_�V�F�[�_�[���쐬
	m_Device->CreateVertexShader(buffer, fsize, NULL, _VertexShader);
	
	// ���_���C�A�E�g(���̓��C�A�E�g)�̒�`
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		// ���_�̈ʒu���i3��float�l�j
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	0,		D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// ���_�̖@���x�N�g�����i3��float�l�j
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	4 * 3,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// ���_�̐F���i4��float�l�FRGBA�j
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	4 * 6,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// ���_�̃e�N�X�`�����W���i2��float�l�j
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0,	4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout); // ���C�A�E�g�̗v�f�����擾

	// �f�o�C�X���g���Ē��_���C�A�E�g���쐬
	m_Device->CreateInputLayout(layout, numElements, buffer, fsize, _VertexLayout);

	delete[] buffer; // �o�b�t�@�̃����������
}

//=================================================================================================
// �s�N�Z���V�F�[�_�[���쐬���鏈��
//=================================================================================================
void Renderer::CreatePixelShader(ID3D11PixelShader** _PixelShader, const char* _FileName)
{
	FILE* file;		// �t�@�C�����J�����߂̃|�C���^
	long int fsize;	// �t�@�C���T�C�Y���i�[����ϐ�

	// �V�F�[�_�[�t�@�C����ReadBinary���[�h�ŊJ��
	fopen_s(&file, _FileName, "rb");	
	// �t�@�C��������ɊJ�������ǂ������m�F
	assert(file);	

	//�t�@�C���T�C�Y���擾
	fsize = _filelength(_fileno(file));	
	// �t�@�C���T�C�Y�Ɋ�Â��ăo�b�t�@���m�F
	unsigned char* buffer = new unsigned char[fsize];	
	// �t�@�C������o�b�t�@�Ƀf�[�^��ǂݍ���
	fread(buffer, fsize, 1, file);	
	// �ǂݍ��݊�����A�t�@�C�������
	fclose(file);	

	// �f�o�C�X���g���ăs�N�Z���V�F�[�_�[���쐬
	m_Device->CreatePixelShader(buffer, fsize, NULL, _PixelShader);

	delete[] buffer;	//�o�b�t�@�̃����������
}