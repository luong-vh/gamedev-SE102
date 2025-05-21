#pragma once
#include "SuperMushroom.h"
#define ID_ANI_ONE_UP_MUSHROOM_NORMAL 141000
#define ID_ANI_ONE_UP_MUSHROOM_RISE 141001
class COneUpMushroom :
    public CSuperMushroom
{
public:
	COneUpMushroom(float x, float y, int _direction, int _state = 0) : CSuperMushroom(x, y, _direction, _state)
	{
	}
	void Render()
	{
		if (state == SUPER_MUSHROOM_STATE_WAITING)
			return;
		CAnimations* animations = CAnimations::GetInstance();
		if (state == SUPER_MUSHROOM_STATE_RISE)
			animations->Get(ID_ANI_ONE_UP_MUSHROOM_RISE)->Render(x, y);
		else
			animations->Get(ID_ANI_ONE_UP_MUSHROOM_NORMAL)->Render(x, y);
	}
};

