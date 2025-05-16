#pragma once
#include "Pipe.h"
#include "VenusFireTrap.h"
class CVenus_Pipe :public CPipe
{
public:
	LPVENUSFIRETRAP venusFireTrap;
	CVenus_Pipe(float x, float y,
		int height,
		 LPVENUSFIRETRAP venus) :CPipe(x, y, height)
	{
		this->venusFireTrap = venus;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};
typedef CVenus_Pipe* LPVenusPipe;