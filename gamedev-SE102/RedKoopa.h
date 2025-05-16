#pragma once
#include "Koopa.h"
#include "KoopaCensor.h"

#define ID_ANI_RED_KOOPA_WALKING_RIGHT 31000
#define ID_ANI_RED_KOOPA_WALKING_LEFT 31010
#define ID_ANI_RED_KOOPA_INSHELL 31100
#define ID_ANI_RED_KOOPA_INSHELL_FLIP 31110
#define ID_ANI_RED_KOOPA_SPINNING 31200
#define ID_ANI_RED_KOOPA_SPINNING_FLIP 31210
#define ID_ANI_RED_KOOPA_REVIVING 31300
#define ID_ANI_RED_KOOPA_REVIVING_FLIP 31310
#define ID_ANI_RED_KOOPA_DIE 31400

class CRedKoopa :
    public CKoopa
{
protected:
	CKoopaCensor* censor;
public:
	CRedKoopa(float x, float y) : CKoopa(x, y)
	{
		censor = new CKoopaCensor(x, y);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int _state);
	void ReverseDirection();
};

