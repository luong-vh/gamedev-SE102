#pragma once
#include "GameObject.h"
#include "Koopa.h"
#include "Goomba.h"
#include "Mario.h"
#define KILL_ZONE_L 0
#define KILL_ZONE_T 455
#define KILL_ZONE_R 3000
#define KILL_ZONE_B 470

class CKillZone :
    public CGameObject
{
public:
    void Render(){}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
	{
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = KILL_ZONE_L;
		t = KILL_ZONE_T;
		r = KILL_ZONE_R;
		b = KILL_ZONE_B;
	}
};

