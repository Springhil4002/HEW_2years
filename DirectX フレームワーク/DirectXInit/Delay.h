#pragma once
#include "Object.h"
class Delay : public Object
{
private:
	std::vector<unsigned> signals;
	bool sig;

public:
	Delay() : sig(false) {}
	~Delay() {}

	// �X�V����
	void Update();

	// �����F�C�ӂ̃t���[������ɐM���𑗂�
	// �\���F{Delay�I�u�W�F�N�g}->SetSignal({�C�ӂ̃t���[����})
	// �ᕶ�Fdelay->SetSignal(10 * FPS);
	void SetSignal(unsigned int _frameCount);
	// �����F����ꂽ�M�����󂯎��
	// �\���Fif({Delay�I�u�W�F�N�g}->GetSignal())
	// �ᕶ�Fif(delay->GetSignal())
	bool GetSignal() const;
};