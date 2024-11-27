#include "Application.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "Camera.h"
#include "Player.h"

const auto ClassName = TEXT("2024 �t���[�����[�N");			// �E�B���h�E�N���X��
const auto WindowName = TEXT("2024 �t���[�����[�N (�`��)");	// �E�B���h�E��

// �}�N����`
#define CLASS_NAME   ClassName	// �E�C���h�E�N���X��
#define WINDOW_NAME  WindowName // �E�B���h�E��

HINSTANCE	Application::m_hInst;		// �C���X�^���X�n���h��
HWND		Application::m_hWnd;		// �E�B���h�E�n���h��
uint32_t	Application::m_Width;		// �E�B���h�E�̉���
uint32_t	Application::m_Height;		// �E�B���h�E�̏c��

//===================================================================
// �R���X�g���N�^
//===================================================================
Application::Application(uint32_t _width, uint32_t _height)
{
	m_Width = _width;
	m_Height = _height;

	timeBeginPeriod(1);
}

//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
Application::~Application()
{
	timeEndPeriod(1);
}

//===================================================================
// ���s�����֐�
//===================================================================
void Application::Run()
{
	if (InitApp())
	{
		MainLoop();
	}

	TermApp();
}

//===================================================================
//����������
//===================================================================
bool Application::InitApp()
{
	// �E�B���h�E�̏�����
	if (!InitWindow())
	{
		return false;
	}

	//����I��
	return true;
} 

//===================================================================
// �E�B���h�E�̏���������
//===================================================================
bool Application::InitWindow()
{
	//�C���X�^���X�n���h�����擾
	auto hInst = GetModuleHandle(nullptr);
	if (hInst == nullptr)
	{
		return false;
	}

	// �E�B���h�E�̐ݒ�
	WNDCLASSEX wc = {};
	wc.cbSize				= sizeof(WNDCLASSEX);
	wc.style				= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc			= WindowProc;
	wc.hIcon				= LoadIcon(hInst, IDI_APPLICATION);
	wc.hCursor				= LoadCursor(hInst, IDC_ARROW);
	wc.hbrBackground		= GetSysColorBrush(COLOR_BACKGROUND);
	wc.lpszMenuName			= nullptr;
	wc.lpszClassName		= CLASS_NAME;
	wc.hIconSm				= LoadIcon(hInst, IDI_APPLICATION);

	// �E�B���h�E�̓o�^
	if (!RegisterClassEx(&wc))
	{
		return false;
	}

	// �C���X�^���X�n���h����ݒ�
	m_hInst = hInst;

	// �E�B���h�E�̃T�C�Y��ݒ�
	RECT rc = {};
	rc.right  = static_cast<LONG>(m_Width);
	rc.bottom = static_cast<LONG>(m_Height);

	// �E�B���h�E�T�C�Y�𒲐�
	auto style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	AdjustWindowRect(&rc, style, FALSE);

	// �E�B���h�E�𐶐�
	m_hWnd = CreateWindowEx(
		0,
		// WS_EX_TOPMOST,
		CLASS_NAME,
		WINDOW_NAME,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr,
		nullptr,
		m_hInst,
		nullptr);
	if (m_hWnd==nullptr)
	{
		return false;
	}

	// �E�B���h�E��\��
	ShowWindow(m_hWnd, SW_SHOWNORMAL);

	// �E�B���h�E���X�V
	UpdateWindow(m_hWnd);

	// �E�B���h�E�Ƀt�H�[�J�X��ݒ�
	SetFocus(m_hWnd);

	// ����I��
	return true;
}

//===================================================================
// �������
//===================================================================
void Application::TermApp()
{
	// �E�B���h�E�̏I������
	TermWindow();
}

//===================================================================
// �E�B���h�E�̉������
//===================================================================
void Application::TermWindow()
{
	// �E�B���h�E�̓o�^������
	if (m_hInst != nullptr)
	{ UnregisterClass(ClassName, m_hInst); }

	m_hInst = nullptr;
	m_hWnd	= nullptr;
}

//===================================================================
// ���C�����[�v
//===================================================================
void Application::MainLoop()
{
	MSG msg = {};

	// �V�[���}�l�[�W���[�̃C���X�^���X����
	SceneManager sm;
	// �J�����̃C���X�^���X����
	Camera camera;

	// �`�揉����
	Renderer::Init();

	// �V�[���}�l�[�W���[������(�^�C�g���V�[���ɐݒ�)
	sm.ChangeScene(sm.TITLE);
	
	// �J����������
	camera.Init();

	// FPS�v���p�ϐ�
	int fpsCounter = 0;
	long long oldTick = GetTickCount64();	// �O��v�����̎���
	long long nowTick = oldTick;			// ����v�����̎���

	// FPS�Œ�p�ϐ�
	LARGE_INTEGER liWork;					// work�����ϐ��͍�Ɨp�ϐ�
	long long frequency;					// �ǂꂭ�炢�ׂ������Ԃ��J�E���g�ł��邩
	QueryPerformanceFrequency(&liWork);
	frequency = liWork.QuadPart;
	// ���ԁi�P�ʁF�J�E���g�j�擾
	QueryPerformanceCounter(&liWork);
	long long oldCount = liWork.QuadPart;	// �O��v�����̎���
	long long nowCount = oldCount;			// ����v�����̎���

	// �Q�[�����[�v
	while (true)
	{
		// �V���Ƀ��b�Z�[�W�������
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// �E�B���h�E�v���V�[�W���Ƀ��b�Z�[�W�𑗂�
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			// �uWM_QUIT�v���b�Z�[�W���󂯎�����烋�[�v�𔲂���
			if (msg.message == WM_QUIT) {
				break;
			}
		}
		else
		{
			QueryPerformanceCounter(&liWork);	//���ݎ��Ԃ��擾
			nowCount = liWork.QuadPart;
			//1/60�b���o�߂�����?
			if (nowCount >= oldCount + frequency / 60) {	//��:60
				// �Q�[���������s

				// �V�[���}�l�[�W���[�X�V����
				sm.Update();
				//�J�����X�V����
				camera.Update();


				// �`��O����
				Renderer::Begin();
				// ���݂̃V�[����`��
				sm.Draw();
				// �J�����`��
				camera.Draw();
				// �`��㏈��
				Renderer::End();

				fpsCounter++;	//�Q�[�����������s������+1����
				oldCount = nowCount;
			}
		}
	}

	// �J�����������
	camera.Uninit();
	// �`��������
	Renderer::Uninit();
}

//=============================================================================
// �E�B���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK Application::WindowProc(HWND _hWnd, UINT _Msg, WPARAM _wP, LPARAM _lP)
{
	switch (_Msg) {
	
	// �E�B���h�E�j���̃��b�Z�[�W
	case WM_DESTROY: {
		// ���uWM_QUIT�v���b�Z�[�W�𑗂�@���@�A�v���I��
		PostQuitMessage(0);
	}
	break;

	// �ux�v�{�^���������ꂽ��
	case WM_CLOSE:	{
		int res = MessageBoxA(NULL, "�I�����܂����H", "�m�F", MB_OKCANCEL);
		if (res == IDOK) {
			// ���uWM_DESTROY�v���b�Z�[�W�𑗂�
			DestroyWindow(_hWnd); 
		}
	}
	break;

	//�L�[���͂����������b�Z�[�W
	case WM_KEYDOWN: {
		if (LOWORD(_wP) == VK_ESCAPE) { //���͂��ꂽ�L�[��ESCAPE�Ȃ�
			PostMessage(_hWnd, WM_CLOSE, _wP, _lP);//�uWM_CLOSE�v�𑗂�
		}
	}
	break;

	default: {
		// �󂯎�������b�Z�[�W�ɑ΂��ăf�t�H���g�̏��������s
		return DefWindowProc(_hWnd, _Msg, _wP, _lP);
		break;
	}

	}
	return 0;
}

