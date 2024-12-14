#include "sound.h"

/* XBOXのプラットフォームと
 それ以外のプラットフォームの
	2パターンの定義 */

// エンディアン(バイトオーダー)の定義
// ※エンディアン:データのバイト順序のこと

// ビッグエンディアン
// ※最上位バイトが最初に来る順序
#ifdef _XBOX 
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

// リトルエンディアン
// ※最下位バイトが最初に来る順序
#ifndef _XBOX 
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Sound::Init()
{
	// 変数宣言
	HRESULT hr;

	HANDLE hFile;
	DWORD  dwChunkSize;
	DWORD  dwChunkPosition;
	DWORD  filetype;

	// COMライブラリの初期化
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		CoUninitialize();
		return -1;
	}

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&m_pXAudio2, 0);		// 第二引数は､動作フラグ デバッグモードの指定(現在は未使用なので0にする)
	if (FAILED(hr)) {
		CoUninitialize();
		return -1;
	}

	// マスターボイスの作成
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);			// 今回はＰＣのデフォルト設定に任せている
	if (FAILED(hr)) {
		if (m_pXAudio2)	m_pXAudio2->Release();
		CoUninitialize();
		return -1;
	}

	// サウンドの初期化
	for (int i = 0; i < SOUND_LABEL_MAX; i++)
	{
		memset(&m_wfx[i], 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&m_buffer[i], 0, sizeof(XAUDIO2_BUFFER));

		hFile = CreateFileA(m_param[i].filename, GENERIC_READ, FILE_SHARE_READ, NULL,
			OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE) {
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
			return HRESULT_FROM_WIN32(GetLastError());
		}

		//　WAVファイルのチャンク読み取り
		FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
		if (filetype != fourccWAVE)		return S_FALSE;

		FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &m_wfx[i], dwChunkSize, dwChunkPosition);

		//　fill out the audio data buffer with the contents of the fourccDATA chunk
		FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
		m_DataBuffer[i] = new BYTE[dwChunkSize];
		ReadChunkData(hFile, m_DataBuffer[i], dwChunkSize, dwChunkPosition);

		CloseHandle(hFile);

		// 読み取ったデータをm_bufferに設定
		m_buffer[i].AudioBytes = dwChunkSize;
		m_buffer[i].pAudioData = m_DataBuffer[i];
		m_buffer[i].Flags = XAUDIO2_END_OF_STREAM;
		// ループ設定に応じてLoopCountを設定
		if (m_param[i].bLoop)
			m_buffer[i].LoopCount = XAUDIO2_LOOP_INFINITE;
		else
			m_buffer[i].LoopCount = 0;

		m_pXAudio2->CreateSourceVoice(&m_pSourceVoice[i], &(m_wfx[i].Format));
	}

	return hr;
}

//=============================================================================
// 解放処理
//=============================================================================
void Sound::Uninit(void)
{
	// サウンドの総数分、サウンドリソースの解放
	for (int i = 0; i < SOUND_LABEL_MAX; i++)
	{
		if (m_pSourceVoice[i])
		{
			m_pSourceVoice[i]->Stop(0);					// サウンドの再生を停止
			m_pSourceVoice[i]->FlushSourceBuffers();	// ソースボイスをクリア
			m_pSourceVoice[i]->DestroyVoice();			// オーディオグラフからソースボイスを削除
			delete[]  m_DataBuffer[i];					// サウンドデータもバッファを解放
		}
	}

	m_pMasteringVoice->DestroyVoice();					// マスターボイスを削除します

	if (m_pXAudio2) m_pXAudio2->Release();				// XAudioオブジェクトを解放

	// COMライブラリの解放
	CoUninitialize();
}

//=============================================================================
// サウンドの再生処理
//=============================================================================
void Sound::Play(SOUND_LABEL label)
{
	// ソースボイスのチェックと破棄
	IXAudio2SourceVoice*& pSV = m_pSourceVoice[(int)label];

	// 既に同じソースボイスが存在してた場合、破棄してnullに設定して停止させる処理
	if (pSV != nullptr)
	{
		pSV->DestroyVoice();
		pSV = nullptr;
	}

	// 新しくソースボイス作成
	m_pXAudio2->CreateSourceVoice(&pSV, &(m_wfx[(int)label].Format));
	pSV->SubmitSourceBuffer(&(m_buffer[(int)label]));	// ボイスキューに新しいオーディオバッファを追加

	// サウンド再生
	pSV->Start(0);

}

//=============================================================================
// サウンドの停止処理
//=============================================================================
void Sound::Stop(SOUND_LABEL label)
{
	// 指定されたソースボイスの存在チェック
	if (m_pSourceVoice[(int)label] == NULL) return;

	// ソースボイスの状態取得
	XAUDIO2_VOICE_STATE xa2state;
	m_pSourceVoice[(int)label]->GetState(&xa2state);
	// バッファがキューにあるか確認
	if (xa2state.BuffersQueued)
	{
		m_pSourceVoice[(int)label]->Stop(0);
	}
}

//=============================================================================
// サウンドの再生再開処理
//=============================================================================
void Sound::Resume(SOUND_LABEL label)
{
	// ソースボイスの取得
	IXAudio2SourceVoice*& pSV = m_pSourceVoice[(int)label];
	// サウンドの再生再開
	pSV->Start();
}



//=============================================================================
// ユーティリティ関数群
//=============================================================================
HRESULT Sound::FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;
	while (hr == S_OK)
	{
		DWORD dwRead;
		if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());
		if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());
		switch (dwChunkType)
		{
		case fourccRIFF:
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());
			break;
		default:
			if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
				return HRESULT_FROM_WIN32(GetLastError());
		}
		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == fourcc)
		{
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}
		dwOffset += dwChunkDataSize;
		if (bytesRead >= dwRIFFDataSize) return S_FALSE;
	}
	return S_OK;
}

HRESULT Sound::ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwRead;
	if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
		hr = HRESULT_FROM_WIN32(GetLastError());
	return hr;
}
