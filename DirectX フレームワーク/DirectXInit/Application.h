#pragma once

#include <Windows.h>
#include <cstdint>

//=============================================================================
// Applicationクラス
//=============================================================================

class Player;
class Application
{
private:
	static HINSTANCE	m_hInst;	// インスタンスハンドル
	static HWND			m_hWnd;		// ウィンドウハンドル
	static uint32_t		m_Width;	// ウィンドウの横幅
	static uint32_t		m_Height;	// ウィンドウの縦幅

	static int fpsCounter;			// fpsカウント変数

	static bool InitApp();			// 初期化処理
	static bool InitWindow();		// ウィンドウの初期化処理
	static void TermApp();			// 解放処理
	static void TermWindow();		// ウィンドウの解放処理
	static void MainLoop();			// メインループ (ゲームループ)

	// ウィンドウプロシージャ関数
	static LRESULT CALLBACK WindowProc
	(HWND _hWnd, UINT _Msg, WPARAM _wP, LPARAM _lP);

public:
	Application(uint32_t _width, uint32_t _height);	//コンストラクタ
	~Application();		//デストラクタ
	void Run();			//実行処理関数

	// 画面の横幅を取得
	static uint32_t GetWidth() {
		return m_Width;
	}

	// 画面の縦幅を取得
	static uint32_t GetHeight() {
		return m_Height;
	}

	// ウィンドウハンドルを返す
	static HWND GetWindow() {
		return m_hWnd;
	}

	// ゲッター・セッター
	static int GetFpsCounter() { return Application::fpsCounter; }
	static void SetFpsCounter(int _fpsCounter) { Application::fpsCounter = _fpsCounter; }
};







