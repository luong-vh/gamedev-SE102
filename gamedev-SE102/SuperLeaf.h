#pragma once
#include "Item.h"

#define ID_ANI_SUPER_LEAF_LEFT 150000
#define ID_ANI_SUPER_LEAF_RIGHT 150001

#define SUPER_LEAF_BBOX_WIDTH 16
#define SUPER_LEAF_BBOX_HEIGHT 14

#define SUPER_LEAF_SPEED 0.07f

#define SUPER_LEAF_STATE_WAITING 0
#define SUPER_LEAF_STATE_RISE 1
#define SUPER_LEAF_STATE_FALLING_LEFT 2
#define SUPER_LEAF_STATE_FALLING_RIGHT 3

#define SUPER_LEAF_DISTANCE_RISE 48

class CSuperLeaf : public CItem
{
public:
	CSuperLeaf(float x, float y, int _state = 0) : CItem(x, y)
	{
		minY = y - SUPER_LEAF_DISTANCE_RISE;
		minX = x;
		maxX = x + SUPER_LEAF_BBOX_WIDTH*2;
		SetState(_state);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	void WakeUp() {
		if (state == SUPER_LEAF_STATE_WAITING) {
			SetState(SUPER_LEAF_STATE_RISE);
		}
	}
	void Delete();
	
};

