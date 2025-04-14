#pragma once
#include "Pipe.h"
#include "PiranhaPlant.h"
class CPiranha_Pipe :
    public CPipe
{
public:
	LPPiranhaPlant piranhaPlant;
	CPiranha_Pipe(float x, float y,
		int height,
		int spriteIdHead, int spriteIdBody, LPPiranhaPlant piranha) :CPipe(x, y, height, spriteIdHead, spriteIdBody)
	{
		this->piranhaPlant = piranha;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};
typedef CPiranha_Pipe* LPPiranhaPipe;

