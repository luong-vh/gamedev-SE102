#include "KoopaCensor.h"

void CKoopaCensor::OnNoCollision(DWORD dt)
{
	isOnPlatform = false;
	y += vy * dt;
}

void CKoopaCensor::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - CENSOR_BBOX_WIDTH / 2;
	top = y - CENSOR_BBOX_HEIGHT / 2;
	right = left + CENSOR_BBOX_WIDTH;
	bottom = top + CENSOR_BBOX_HEIGHT;
}
void CKoopaCensor::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == CENSOR_STATE_WAITING)
	{
		return;
	}
	vy += ay * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CKoopaCensor::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CENSOR_STATE_WAITING:
		ay = 0;
		vy = 0;
		break;
	case CENSOR_STATE_ACTIVE:
		ay = CENSOR_GRAVITY;
		break;
	}
}
void CKoopaCensor::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0)
		{
			isOnPlatform = true;
		}
	}
	
}