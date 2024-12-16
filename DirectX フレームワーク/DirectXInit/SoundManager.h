#pragma once
#include "sound.h"

class SoundManager {
private:
	Sound m_Sound;		// �T�E���h�̃C���X�^���X
public:
	HRESULT Init();		// ����������
	void Uninit();		// �������
		
	void Play(SOUND_LABEL _label);		// �T�E���h�Đ�
	void Stop(SOUND_LABEL _label);		// �T�E���h��~
	void Resume(SOUND_LABEL _label);	// �T�E���h�̍Đ��ĊJ
};


