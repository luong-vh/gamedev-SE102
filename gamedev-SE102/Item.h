#pragma once
#include "GameObject.h"
class CItem :
    public CGameObject
{
protected:
	float minY, maxY;
	float minX, maxX;
public:
	int IsCollidable() { return 1; }	
	int IsBlocking() { return 0; }
	virtual void WakeUp() {}
	virtual void OnCollisionWithMario(LPCOLLISIONEVENT e) {}
	CItem(float x, float y) : CGameObject(x, y){}
};
typedef CItem* LPItem;

