#pragma once
#include <xaudio2.h>
#include <vector>

// �T�E���h�t�@�C���̃��x����`
enum SOUND_LABEL {
	SOUND_LABEL_BGM001 = 0,		// BGM_1
	SOUND_LABEL_BGM002,			// BGM_2
	SOUND_LABEL_BGM003,			// BGM_3
	SOUND_LABEL_BGM004,			// BGM_4
	SOUND_LABEL_BGM005,			// BGM_5

	SOUND_LABEL_SE001,			// SE_1
	SOUND_LABEL_SE002,			// SE_2
	SOUND_LABEL_SE003,			// SE_3
	SOUND_LABEL_SE004,			// SE_4
	SOUND_LABEL_SE005,			// SE_5
	SOUND_LABEL_SE006,			// SE_6
	SOUND_LABEL_SE007,			// SE_7
	SOUND_LABEL_SE008,			// SE_8
	SOUND_LABEL_SE009,			// SE_9
	SOUND_LABEL_SE010,			// SE_10

	SOUND_LABEL_MAX				// �T�E���h�t�@�C���̑���
};

class Sound {
private:
	// �p�����[�^�\����
	struct PARAM
	{
		LPCSTR filename;	// �����t�@�C���܂ł̃p�X��ݒ�
		bool bLoop;			// true�Ń��[�v �ʏ�,BGM��ture�ESE��false
	};

	// �e�T�E���h�t�@�C���̃p�X�ƃ��[�v�ݒ�̏�����
	PARAM m_param[SOUND_LABEL_MAX] =
	{
		{"asset/BGM/�����F�̃J�[�y�b�g.wav"			, true},	// BGM_1�@�^�C�g��
		{"asset/BGM/�ق�̂肢�������ȃs�A�m.wav"		, true},	// BGM_2�@�z�[��
		{"asset/BGM/����ɒ��ތÏ�.wav"				, true},	// BGM_3�@�Q�[��
		{"asset/BGM/Waltz-Antiqua.wav"			, true},	// BGM_4�@�Q�[���I�[�o�[
		{"asset/BGM/�V���g���[���u���N�̊w�ю�.wav"	, true},	// BGM_5�@���U���g

		{"asset/SE/�^�C�g�����艹.wav"				, false},	// SE_1�@ �^�C�g�����艹
		{"asset/SE/�A�C�R�����艹.wav"				, false},	// SE_2	�@�A�C�R�����艹�@
		{"asset/SE/�A�C�R���I����.wav"				, false},	// SE_3�@ �A�C�R���I����
		{"asset/SE/����.wav"						, false},	// SE_4�@ �v���C���[����
		{"asset/SE/�W�����v��.wav"					, false},	// SE_5�@ �v���C���[�W�����v��
		{"asset/SE/�͂�.wav"						, false},	// SE_6�@ �o���h��͂މ�
		{"asset/SE/Band_Pull.wav"				, false},	// SE_7�@ �o���h��������
		{"asset/SE/Band_OverPull.wav"			, false},	// SE_8�@ �o���h��������������
		{"asset/SE/�j�Њl����.wav"					, false},	// SE_9�@ �`�b�v�l����
		{"asset/SE/�S�[�����J��.wav"				, false}	// SE_10�@�S�[����
	};

	// XAudio2�C���^�[�t�F�[�X�ւ̃|�C���^
	IXAudio2* m_pXAudio2 = NULL;
	// �}�X�^�[�{�C�X�ւ̃|�C���^
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;
	// �e�T�E���h�̃\�[�X�{�C�X�ւ̃|�C���^
	IXAudio2SourceVoice* m_pSourceVoice[SOUND_LABEL_MAX];
	// �e�T�E���h��WAV�t�H�[�}�b�g���
	WAVEFORMATEXTENSIBLE m_wfx[SOUND_LABEL_MAX];
	// �e�T�E���h�̃o�b�t�@���
	XAUDIO2_BUFFER m_buffer[SOUND_LABEL_MAX];
	// �e�T�E���h�̃f�[�^�o�b�t�@
	std::vector<BYTE> m_DataBuffer[SOUND_LABEL_MAX];

	// �w�肳�ꂽ�`�����N���ʎq�����f�[�^�`�����N���t�@�C�������猩����
	HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
	// �w�肳�ꂽ�ʒu����f�[�^�`�����N��ǂݎ��
	HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

public:
	// �Q�[�����[�v�J�n�O�ɌĂяo���T�E���h�̏���������
	HRESULT Init(void);

	// �Q�[�����[�v�I����ɌĂяo���T�E���h�̉������
	void Uninit(void);

	// �����Ŏw�肵���T�E���h���Đ�����
	void Play(SOUND_LABEL _label);

	// �����Ŏw�肵���T�E���h���~����
	void Stop(SOUND_LABEL _label);

	// �����Ŏw�肵���T�E���h�̍Đ����ĊJ����
	void Resume(SOUND_LABEL _label);

};