#include "BandTip.h"
#include "Band.h"

void BandTip::Update()
{
	if (band->status != Band::STOP)
	{
		Physic::Update();
	}
}