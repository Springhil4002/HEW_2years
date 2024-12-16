#include "SoundManager.h"

// ����������
HRESULT SoundManager::Init() 
{
	return m_Sound.Init();
}

// �������
void SoundManager::Uninit()
{
	m_Sound.Uninit();
}

// �T�E���h�Đ�
void SoundManager::Play(SOUND_LABEL _label)
{
	m_Sound.Play(_label);
}

// �T�E���h��~
void SoundManager::Stop(SOUND_LABEL _label)
{
	m_Sound.Stop(_label);
}

// �T�E���h�̍Đ��ĊJ
void SoundManager::Resume(SOUND_LABEL _label)
{
	m_Sound.Resume(_label);
}


