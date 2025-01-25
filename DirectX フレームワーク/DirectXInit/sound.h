#pragma once
#include <xaudio2.h>
#include <vector>

// サウンドファイルのラベル定義
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

	SOUND_LABEL_MAX				// サウンドファイルの総数
};

class Sound {
private:
	// パラメータ構造体
	struct PARAM
	{
		LPCSTR filename;	// 音声ファイルまでのパスを設定
		bool bLoop;			// trueでループ 通常,BGMはture・SEはfalse
	};

	// 各サウンドファイルのパスとループ設定の初期化
	PARAM m_param[SOUND_LABEL_MAX] =
	{
		{"asset/BGM/黄金色のカーペット.wav"			, true},	// BGM_1　タイトル
		{"asset/BGM/ほんのりいい感じなピアノ.wav"		, true},	// BGM_2　ホーム
		{"asset/BGM/水底に沈む古城.wav"				, true},	// BGM_3　ゲーム
		{"asset/BGM/Waltz-Antiqua.wav"			, true},	// BGM_4　ゲームオーバー
		{"asset/BGM/シュトラールブルクの学び舎.wav"	, true},	// BGM_5　リザルト

		{"asset/SE/タイトル決定音.wav"				, false},	// SE_1　 タイトル決定音
		{"asset/SE/アイコン決定音.wav"				, false},	// SE_2	　アイコン決定音　
		{"asset/SE/アイコン選択音.wav"				, false},	// SE_3　 アイコン選択音
		{"asset/SE/足音.wav"						, false},	// SE_4　 プレイヤー足音
		{"asset/SE/ジャンプ音.wav"					, false},	// SE_5　 プレイヤージャンプ音
		{"asset/SE/掴む.wav"						, false},	// SE_6　 バンドを掴む音
		{"asset/SE/Band_Pull.wav"				, false},	// SE_7　 バンドを引く音
		{"asset/SE/Band_OverPull.wav"			, false},	// SE_8　 バンドを引きすぎた音
		{"asset/SE/破片獲得音.wav"					, false},	// SE_9　 チップ獲得音
		{"asset/SE/ゴール扉開閉音.wav"				, false}	// SE_10　ゴール音
	};

	// XAudio2インターフェースへのポインタ
	IXAudio2* m_pXAudio2 = NULL;
	// マスターボイスへのポインタ
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;
	// 各サウンドのソースボイスへのポインタ
	IXAudio2SourceVoice* m_pSourceVoice[SOUND_LABEL_MAX];
	// 各サウンドのWAVフォーマット情報
	WAVEFORMATEXTENSIBLE m_wfx[SOUND_LABEL_MAX];
	// 各サウンドのバッファ情報
	XAUDIO2_BUFFER m_buffer[SOUND_LABEL_MAX];
	// 各サウンドのデータバッファ
	std::vector<BYTE> m_DataBuffer[SOUND_LABEL_MAX];

	// 指定されたチャンク識別子を持つデータチャンクをファイル内から見つける
	HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
	// 指定された位置からデータチャンクを読み取る
	HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

public:
	// ゲームループ開始前に呼び出すサウンドの初期化処理
	HRESULT Init(void);

	// ゲームループ終了後に呼び出すサウンドの解放処理
	void Uninit(void);

	// 引数で指定したサウンドを再生する
	void Play(SOUND_LABEL _label);

	// 引数で指定したサウンドを停止する
	void Stop(SOUND_LABEL _label);

	// 引数で指定したサウンドの再生を再開する
	void Resume(SOUND_LABEL _label);

};