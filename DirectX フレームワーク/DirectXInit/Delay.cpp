#include "Delay.h"

void Delay::Update()
{
	sig = false;
	for (auto& signal : signals)
	{
		if (signal > 0)
		{
			signal--;
		}
		else
		{
			sig = true;
		}
	}

	if (sig)
	{
		auto newEnd = remove(signals.begin(), signals.end(), 0);
		signals.erase(newEnd, signals.end());
	}
}

void Delay::SetSignal(unsigned int _frameCount)
{
	signals.push_back(_frameCount);
}

bool Delay::GetSignal() const
{
	return sig;
}