#include "BandTip.h"
#include "Band.h"

void BandTip::Update()
{
	if (band->status == Band::DEFAULT)
	{
		Physic::Update();
	}
}