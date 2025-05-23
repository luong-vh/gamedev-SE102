#include "ParaKoopa.h"
#include "KillZone.h"

CParaKoopa::CParaKoopa(float x, float y) : CKoopa(x, y)
{
	isPara = true;
}

void CParaKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isPara && state == KOOPA_STATE_WALKING) 
	{
		vy += ay * dt;
		vx += ax * dt;
		if (isOnPlatform) {
			vy = -PARA_KOOPA_FLY_SPEED_Y;
		}
		CCollision::GetInstance()->Process(this, dt, coObjects);
		return;
	}
	CKoopa::Update(dt, coObjects);
}

void CParaKoopa::GetAniId(int& aniId)
{
	if (isPara && state == KOOPA_STATE_WALKING) {
	
		if (direction > 0) aniId = ID_ANI_PARA_KOOPA_WALKING_RIGHT;
		else aniId = ID_ANI_PARA_KOOPA_WALKING_LEFT;
		return;
	}
	CKoopa::GetAniId(aniId);
}

void CParaKoopa::SetState(int _state)
{
	state = _state;
	state_start = GetTickCount64();
	switch (_state)
	{
	case KOOPA_STATE_WAITING:
		isBeingHeld = false;
		vx = 0;
		vy = 0;
		ax = 0;
		ay = 0;
		x = start_x;
		y = start_y + 500;
		isPara = true;
		break;
	case KOOPA_STATE_WALKING:

		isFlipped = false;
		isBeingHeld = false;
		ay = KOOPA_GRAVITY / 2;
		vx = direction * KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_DIE:
		ay = KOOPA_GRAVITY;
		vy = KOOPA_DIE_SPEED_BY_KOOPA;
		isBeingHeld = false;
		isPara = false;
		break;
	case KOOPA_STATE_INSHELL:

	case KOOPA_STATE_REVIVING:
		vx = 0;
		ay = KOOPA_GRAVITY ;
		ax = 0;
		isPara = false;
		break;
	case KOOPA_STATE_SPINNING:
		isPara = false;
		isBeingHeld = false;
		ay = KOOPA_GRAVITY;
		vx = direction * KOOPA_SPINNING_SPEED;
		break;
	default:

		break;
	}

}


void CParaKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (isPara) {
		if (dynamic_cast<CKillZone*>(e->obj)) {
			SetState(KOOPA_STATE_WAITING);
		}
		else if (e->ny != 0 && e->obj->IsBlocking())
		{
			vy = 0;
			if (e->ny < 0) isOnPlatform = true;
		}
		
		else if (dynamic_cast<CKoopa*>(e->obj)) {
			if (e->obj->GetState() == KOOPA_STATE_DIE) return;
			if (e->obj->GetState() == KOOPA_STATE_SPINNING) GetKoopaHit(-e->nx);
			else if (((CKoopa*)e->obj)->isBeingHeld) {
				GetKoopaHit(nx);
				((CKoopa*)e->obj)->GetKoopaHit(-nx);
			}
			return;
		}
		else if (e->ny != 0) ReverseDirection();
		return;
	}
	CKoopa::OnCollisionWith(e);
}

