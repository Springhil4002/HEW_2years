#include "sound.h"

/* XBOX�̃v���b�g�t�H�[����
 ����ȊO�̃v���b�g�t�H�[����
	2�p�^�[���̒�` */

// �G���f�B�A��(�o�C�g�I�[�_�[)�̒�`
// ���G���f�B�A��:�f�[�^�̃o�C�g�����̂���

// �r�b�O�G���f�B�A��
// ���ŏ�ʃo�C�g���ŏ��ɗ��鏇��
#ifdef _XBOX 
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

// ���g���G���f�B�A��
// ���ŉ��ʃo�C�g���ŏ��ɗ��鏇��
#ifndef _XBOX 
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

//=============================================================================
// ����������
//=============================================================================
HRESULT Sound::Init()
{
	// �ϐ��錾
	HRESULT hr;

	HANDLE hFile;
	DWORD  dwChunkSize;
	DWORD  dwChunkPosition;
	DWORD  filetype;

	// COM���C�u�����̏�����
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		CoUninitialize();
		return -1;
	}

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&m_pXAudio2, 0);		// �������ͤ����t���O �f�o�b�O���[�h�̎w��(���݂͖��g�p�Ȃ̂�0�ɂ���)
	if (FAILED(hr)) {
		CoUninitialize();
		return -1;
	}

	// �}�X�^�[�{�C�X�̍쐬
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);			// ����͂o�b�̃f�t�H���g�ݒ�ɔC���Ă���
	if (FAILED(hr)) {
		if (m_pXAudio2)	m_pXAudio2->Release();
		CoUninitialize();
		return -1;
	}

	// �T�E���h�̏�����
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

		//�@WAV�t�@�C���̃`�����N�ǂݎ��
		FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
		if (filetype != fourccWAVE)		return S_FALSE;

		FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &m_wfx[i], dwChunkSize, dwChunkPosition);

		//�@fill out the audio data buffer with the contents of the fourccDATA chunk
		FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
		m_DataBuffer[i] = new BYTE[dwChunkSize];
		ReadChunkData(hFile, m_DataBuffer[i], dwChunkSize, dwChunkPosition);

		CloseHandle(hFile);

		// �ǂݎ�����f�[�^��m_buffer�ɐݒ�
		m_buffer[i].AudioBytes = dwChunkSize;
		m_buffer[i].pAudioData = m_DataBuffer[i];
		m_buffer[i].Flags = XAUDIO2_END_OF_STREAM;
		// ���[�v�ݒ�ɉ�����LoopCount��ݒ�
		if (m_param[i].bLoop)
			m_buffer[i].LoopCount = XAUDIO2_LOOP_INFINITE;
		else
			m_buffer[i].LoopCount = 0;

		m_pXAudio2->CreateSourceVoice(&m_pSourceVoice[i], &(m_wfx[i].Format));
	}

	return hr;
}

//=============================================================================
// �������
//=============================================================================
void Sound::Uninit(void)
{
	// �T�E���h�̑������A�T�E���h���\�[�X�̉��
	for (int i = 0; i < SOUND_LABEL_MAX; i++)
	{
		if (m_pSourceVoice[i])
		{
			m_pSourceVoice[i]->Stop(0);					// �T�E���h�̍Đ����~
			m_pSourceVoice[i]->FlushSourceBuffers();	// �\�[�X�{�C�X���N���A
			m_pSourceVoice[i]->DestroyVoice();			// �I�[�f�B�I�O���t����\�[�X�{�C�X���폜
			delete[]  m_DataBuffer[i];					// �T�E���h�f�[�^���o�b�t�@�����
		}
	}

	m_pMasteringVoice->DestroyVoice();					// �}�X�^�[�{�C�X���폜���܂�

	if (m_pXAudio2) m_pXAudio2->Release();				// XAudio�I�u�W�F�N�g�����

	// COM���C�u�����̉��
	CoUninitialize();
}

//=============================================================================
// �T�E���h�̍Đ�����
//=============================================================================
void Sound::Play(SOUND_LABEL label)
{
	// �\�[�X�{�C�X�̃`�F�b�N�Ɣj��
	IXAudio2SourceVoice*& pSV = m_pSourceVoice[(int)label];

	// ���ɓ����\�[�X�{�C�X�����݂��Ă��ꍇ�A�j������null�ɐݒ肵�Ē�~�����鏈��
	if (pSV != nullptr)
	{
		pSV->DestroyVoice();
		pSV = nullptr;
	}

	// �V�����\�[�X�{�C�X�쐬
	m_pXAudio2->CreateSourceVoice(&pSV, &(m_wfx[(int)label].Format));
	pSV->SubmitSourceBuffer(&(m_buffer[(int)label]));	// �{�C�X�L���[�ɐV�����I�[�f�B�I�o�b�t�@��ǉ�

	// �T�E���h�Đ�
	pSV->Start(0);

}

//=============================================================================
// �T�E���h�̒�~����
//=============================================================================
void Sound::Stop(SOUND_LABEL label)
{
	// �w�肳�ꂽ�\�[�X�{�C�X�̑��݃`�F�b�N
	if (m_pSourceVoice[(int)label] == NULL) return;

	// �\�[�X�{�C�X�̏�Ԏ擾
	XAUDIO2_VOICE_STATE xa2state;
	m_pSourceVoice[(int)label]->GetState(&xa2state);
	// �o�b�t�@���L���[�ɂ��邩�m�F
	if (xa2state.BuffersQueued)
	{
		m_pSourceVoice[(int)label]->Stop(0);
	}
}

//=============================================================================
// �T�E���h�̍Đ��ĊJ����
//=============================================================================
void Sound::Resume(SOUND_LABEL label)
{
	// �\�[�X�{�C�X�̎擾
	IXAudio2SourceVoice*& pSV = m_pSourceVoice[(int)label];
	// �T�E���h�̍Đ��ĊJ
	pSV->Start();
}



//=============================================================================
// ���[�e�B���e�B�֐��Q
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
