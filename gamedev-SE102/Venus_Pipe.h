#pragma once
#include "Pipe.h"
#include "VenusFireTrap.h"
class CVenus_Pipe :public CPipe
{
public:
	LPVENUSFIRETRAP venusFireTrap;
	CVenus_Pipe(float x, float y,
		int height,
		int spriteIdHead, int spriteIdBody, LPVENUSFIRETRAP venus) :CPipe(x, y, height, spriteIdHead, spriteIdBody)
	{
		this->venusFireTrap = venus;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};
typedef CVenus_Pipe* LPVenusPipe;