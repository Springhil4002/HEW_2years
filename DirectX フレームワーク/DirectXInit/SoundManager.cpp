#include "SoundManager.h"

// 初期化処理
HRESULT SoundManager::Init() 
{
	return m_Sound.Init();
}

// 解放処理
void SoundManager::Uninit()
{
	m_Sound.Uninit();
}

// サウンド再生
void SoundManager::Play(SOUND_LABEL _label)
{
	m_Sound.Play(_label);
}

// サウンド停止
void SoundManager::Stop(SOUND_LABEL _label)
{
	m_Sound.Stop(_label);
}

// サウンドの再生再開
void SoundManager::Resume(SOUND_LABEL _label)
{
	m_Sound.Resume(_label);
}


