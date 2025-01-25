#pragma once

#include <Windows.h>
#include <cstdint>

//=============================================================================
// Application�N���X
//=============================================================================

class Player;
class Application
{
private:
	static HINSTANCE	m_hInst;	// �C���X�^���X�n���h��
	static HWND			m_hWnd;		// �E�B���h�E�n���h��
	static uint32_t		m_Width;	// �E�B���h�E�̉���
	static uint32_t		m_Height;	// �E�B���h�E�̏c��

	static int fpsCounter;			// fps�J�E���g�ϐ�

	static bool InitApp();			// ����������
	static bool InitWindow();		// �E�B���h�E�̏���������
	static void TermApp();			// �������
	static void TermWindow();		// �E�B���h�E�̉������
	static void MainLoop();			// ���C�����[�v (�Q�[�����[�v)

	// �E�B���h�E�v���V�[�W���֐�
	static LRESULT CALLBACK WindowProc
	(HWND _hWnd, UINT _Msg, WPARAM _wP, LPARAM _lP);

public:
	Application(uint32_t _width, uint32_t _height);	//�R���X�g���N�^
	~Application();		//�f�X�g���N�^
	void Run();			//���s�����֐�

	// ��ʂ̉������擾
	static uint32_t GetWidth() {
		return m_Width;
	}

	// ��ʂ̏c�����擾
	static uint32_t GetHeight() {
		return m_Height;
	}

	// �E�B���h�E�n���h����Ԃ�
	static HWND GetWindow() {
		return m_hWnd;
	}

	// �Q�b�^�[�E�Z�b�^�[
	static int GetFpsCounter() { return Application::fpsCounter; }
	static void SetFpsCounter(int _fpsCounter) { Application::fpsCounter = _fpsCounter; }
};







