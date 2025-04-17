#pragma once

#include "Item.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN_NORMAL 40000
#define ID_ANI_COIN_BRICK 40010
#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

#define COIN_SPEED 0.25f
#define COIN_STATE_NORMAL 0
#define COIN_STATE_MOVING_UP 1
#define COIN_STATE_MOVING_DOWN 2
#define COIN_STATE_WAITING 3
class CCoin : public CItem {
public:
	CCoin(float x, float y, int _state = 0) : CItem(x, y) 
	{
		
		maxY = y - COIN_BBOX_HEIGHT;
		minY = maxY - COIN_BBOX_HEIGHT * 3;
		SetState(_state);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void SetState(int state);
	void WakeUp() {
		if (state == COIN_STATE_WAITING) {
			SetState(COIN_STATE_MOVING_UP);
		}
	}
	int IsCollidable() {
		if (state == COIN_STATE_WAITING)
			return 0;
		return 1;
	}
};