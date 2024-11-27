#include "Application.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "Camera.h"
#include "Player.h"

const auto ClassName = TEXT("2024 フレームワーク");			// ウィンドウクラス名
const auto WindowName = TEXT("2024 フレームワーク (描画)");	// ウィンドウ名

// マクロ定義
#define CLASS_NAME   ClassName	// ウインドウクラス名
#define WINDOW_NAME  WindowName // ウィンドウ名

HINSTANCE	Application::m_hInst;		// インスタンスハンドル
HWND		Application::m_hWnd;		// ウィンドウハンドル
uint32_t	Application::m_Width;		// ウィンドウの横幅
uint32_t	Application::m_Height;		// ウィンドウの縦幅

//===================================================================
// コンストラクタ
//===================================================================
Application::Application(uint32_t _width, uint32_t _height)
{
	m_Width = _width;
	m_Height = _height;

	timeBeginPeriod(1);
}

//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
Application::~Application()
{
	timeEndPeriod(1);
}

//===================================================================
// 実行処理関数
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
//初期化処理
//===================================================================
bool Application::InitApp()
{
	// ウィンドウの初期化
	if (!InitWindow())
	{
		return false;
	}

	//正常終了
	return true;
} 

//===================================================================
// ウィンドウの初期化処理
//===================================================================
bool Application::InitWindow()
{
	//インスタンスハンドルを取得
	auto hInst = GetModuleHandle(nullptr);
	if (hInst == nullptr)
	{
		return false;
	}

	// ウィンドウの設定
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

	// ウィンドウの登録
	if (!RegisterClassEx(&wc))
	{
		return false;
	}

	// インスタンスハンドルを設定
	m_hInst = hInst;

	// ウィンドウのサイズを設定
	RECT rc = {};
	rc.right  = static_cast<LONG>(m_Width);
	rc.bottom = static_cast<LONG>(m_Height);

	// ウィンドウサイズを調整
	auto style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	AdjustWindowRect(&rc, style, FALSE);

	// ウィンドウを生成
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

	// ウィンドウを表示
	ShowWindow(m_hWnd, SW_SHOWNORMAL);

	// ウィンドウを更新
	UpdateWindow(m_hWnd);

	// ウィンドウにフォーカスを設定
	SetFocus(m_hWnd);

	// 正常終了
	return true;
}

//===================================================================
// 解放処理
//===================================================================
void Application::TermApp()
{
	// ウィンドウの終了処理
	TermWindow();
}

//===================================================================
// ウィンドウの解放処理
//===================================================================
void Application::TermWindow()
{
	// ウィンドウの登録を解除
	if (m_hInst != nullptr)
	{ UnregisterClass(ClassName, m_hInst); }

	m_hInst = nullptr;
	m_hWnd	= nullptr;
}

//===================================================================
// メインループ
//===================================================================
void Application::MainLoop()
{
	MSG msg = {};

	// シーンマネージャーのインスタンス生成
	SceneManager sm;
	// カメラのインスタンス生成
	Camera camera;

	// 描画初期化
	Renderer::Init();

	// シーンマネージャー初期化(タイトルシーンに設定)
	sm.ChangeScene(sm.TITLE);
	
	// カメラ初期化
	camera.Init();

	// FPS計測用変数
	int fpsCounter = 0;
	long long oldTick = GetTickCount64();	// 前回計測時の時間
	long long nowTick = oldTick;			// 今回計測時の時間

	// FPS固定用変数
	LARGE_INTEGER liWork;					// workがつく変数は作業用変数
	long long frequency;					// どれくらい細かく時間をカウントできるか
	QueryPerformanceFrequency(&liWork);
	frequency = liWork.QuadPart;
	// 時間（単位：カウント）取得
	QueryPerformanceCounter(&liWork);
	long long oldCount = liWork.QuadPart;	// 前回計測時の時間
	long long nowCount = oldCount;			// 今回計測時の時間

	// ゲームループ
	while (true)
	{
		// 新たにメッセージがあれば
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// ウィンドウプロシージャにメッセージを送る
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			// 「WM_QUIT」メッセージを受け取ったらループを抜ける
			if (msg.message == WM_QUIT) {
				break;
			}
		}
		else
		{
			QueryPerformanceCounter(&liWork);	//現在時間を取得
			nowCount = liWork.QuadPart;
			//1/60秒が経過したか?
			if (nowCount >= oldCount + frequency / 60) {	//元:60
				// ゲーム処理実行

				// シーンマネージャー更新処理
				sm.Update();
				//カメラ更新処理
				camera.Update();


				// 描画前処理
				Renderer::Begin();
				// 現在のシーンを描画
				sm.Draw();
				// カメラ描画
				camera.Draw();
				// 描画後処理
				Renderer::End();

				fpsCounter++;	//ゲーム処理を実行したら+1する
				oldCount = nowCount;
			}
		}
	}

	// カメラ解放処理
	camera.Uninit();
	// 描画解放処理
	Renderer::Uninit();
}

//=============================================================================
// ウィンドウプロシージャ
//=============================================================================
LRESULT CALLBACK Application::WindowProc(HWND _hWnd, UINT _Msg, WPARAM _wP, LPARAM _lP)
{
	switch (_Msg) {
	
	// ウィンドウ破棄のメッセージ
	case WM_DESTROY: {
		// ↓「WM_QUIT」メッセージを送る　→　アプリ終了
		PostQuitMessage(0);
	}
	break;

	// 「x」ボタンが押されたら
	case WM_CLOSE:	{
		int res = MessageBoxA(NULL, "終了しますか？", "確認", MB_OKCANCEL);
		if (res == IDOK) {
			// ↓「WM_DESTROY」メッセージを送る
			DestroyWindow(_hWnd); 
		}
	}
	break;

	//キー入力があったメッセージ
	case WM_KEYDOWN: {
		if (LOWORD(_wP) == VK_ESCAPE) { //入力されたキーがESCAPEなら
			PostMessage(_hWnd, WM_CLOSE, _wP, _lP);//「WM_CLOSE」を送る
		}
	}
	break;

	default: {
		// 受け取ったメッセージに対してデフォルトの処理を実行
		return DefWindowProc(_hWnd, _Msg, _wP, _lP);
		break;
	}

	}
	return 0;
}

