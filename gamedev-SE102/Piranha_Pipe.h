#pragma once
#include "Pipe.h"
#include "PiranhaPlant.h"
class CPiranha_Pipe :
    public CPipe
{
public:
	LPPIRANHAPLANT piranhaPlant;
	CPiranha_Pipe(float x, float y, int height, LPPIRANHAPLANT piranha) :CPipe(x, y, height)
	{
		this->piranhaPlant = piranha;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};
typedef CPiranha_Pipe* LPPIRANHAPIPE;

