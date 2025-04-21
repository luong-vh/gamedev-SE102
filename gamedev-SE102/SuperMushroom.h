#pragma once
#include "Item.h"

#define ID_ANI_SUPER_MUSHROOM_NORMAL 140000
#define ID_ANI_SUPER_MUSHROOM_RISE 140001


#define SUPER_MUSHROOM_BBOX_WIDTH 16
#define SUPER_MUSHROOM_BBOX_HEIGHT 16

#define SUPER_MUSHROOM_GRAVITY 0.003f

#define SUPER_MUSHROOM_SPEED_RISE 0.01f
#define SUPER_MUSHROOM_SPEED_X 0.07f

#define SUPER_MUSHROOM_STATE_WAITING 0
#define SUPER_MUSHROOM_STATE_RISE 1
#define SUPER_MUSHROOM_STATE_MOVING 2

#define SUPER_MUSHROOM_TIMEOUT_RISE 1100
class CSuperMushroom :
    public CItem
{
private:
	int direction;
	bool isOnPlatform;
	int timeState;
public:
	CSuperMushroom(float x, float y, int _direction, int _state = 0) : CItem(x, y)
	{
		direction = _direction;
		minY = y - SUPER_MUSHROOM_BBOX_HEIGHT;
		SetState(_state);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnNoCollision(DWORD dt) {
		x += vx * dt;
		y += vy * dt;
	}
	void OnCollisionWith(LPCOLLISIONEVENT e) {
		if (!e->obj->IsBlocking()) return;
		if (state == SUPER_MUSHROOM_STATE_MOVING)
		{
			if (e->ny != 0)
			{
				vy = 0;
			}
			else if (e->nx != 0)
			{
				vx = -vx;
			}
		}
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void SetState(int state);
	void WakeUp() {
		if (state == SUPER_MUSHROOM_STATE_WAITING) {
			SetState(SUPER_MUSHROOM_STATE_RISE);
		}
	}
	void Delete();
	int IsCollidable() {
		return 1;
	}
};

