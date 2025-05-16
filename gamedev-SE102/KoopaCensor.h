#pragma once
#include "GameObject.h"
#define CENSOR_GRAVITY 0.02f
#define CENSOR_BBOX_WIDTH 1
#define CENSOR_BBOX_HEIGHT 18
#define CENSOR_STATE_WAITING 0
#define CENSOR_STATE_ACTIVE 1
class CKoopaCensor :
    public CGameObject
{
	bool isOnPlatform;
	float ay;
public:
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	CKoopaCensor(float x, float y) : CGameObject(x, y)
	{
		this->ay = CENSOR_GRAVITY;
		isOnPlatform = true;
		SetState(CENSOR_STATE_WAITING);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render()
	{
		RenderBoundingBox();
	}
	void Activate()
	{
		SetState(CENSOR_STATE_ACTIVE);
	}
	void Deactivate()
	{
		SetState(CENSOR_STATE_WAITING);
	}
	void SetX(float x)
	{
		this->x = x;
	}
	int IsBlocking() { return 0; }
	bool IsOnPlatform() { return isOnPlatform; }

};

