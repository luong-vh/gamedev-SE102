#pragma once
#include "Koopa.h"
#define ID_ANI_PARA_KOOPA_WALKING_RIGHT 32000
#define ID_ANI_PARA_KOOPA_WALKING_LEFT 32010
#define PARA_KOOPA_FLY_SPEED_Y 0.20f
class CParaKoopa :
    public CKoopa
{
private:
	bool isPara;
public:
	CParaKoopa(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetAniId(int& aniId);
	void SetState(int state);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	
};

