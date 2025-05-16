#include "ParaGoomba.h"
#include "debug.h"
#include "Game.h"
#include "Koopa.h"
CGoomba::CGoomba(float x, float y):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(GOOMBA_STATE_WAITING);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{ 
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}

}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
void CGoomba::WakeUp()
{
	SetState(GOOMBA_STATE_WALKING);
}


void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CGoomba*>(e->obj)) {
		if (e->obj->GetState() == GOOMBA_STATE_PARA || e->obj->GetState() == GOOMBA_STATE_DIE) return;
		OnCollisionWithGoomba(e);
		return;
	}
	if (dynamic_cast<CKoopa*>(e->obj)) {
		if (e->obj->GetState() == KOOPA_STATE_DIE) return;
		OnCollisionWithKoopa(e);
		return;
	}
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		ReverseDirection();
	}
}
void CGoomba::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	if (e->nx != 0)
	{
		ReverseDirection();
		((CGoomba*)e->obj)->ReverseDirection();
	}
}
void CGoomba::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	if (((CKoopa*)e->obj)->isBeingHeld && ! this->IsDeleted()) {
		GetKoopaHit(nx);
		((CKoopa*)e->obj)->GetKoopaHit(-nx);
		return;
	}
	if (state == GOOMBA_STATE_PARA) return;
	if (e->nx != 0)
	{
		if (e->obj->GetState() == KOOPA_STATE_SPINNING) GetKoopaHit(-e->nx);
		else {
			ReverseDirection();
			((CKoopa*)e->obj)->ReverseDirection();
		}
	}
}
void CGoomba::GetStomped()
{
	if (state == GOOMBA_STATE_DIE
		|| state == GOOMBA_STATE_DIE_BY_TAIL
		|| state == GOOMBA_STATE_DIE_BY_KOOPA
		) return;
	SetState(GOOMBA_STATE_DIE);
}
void CGoomba::GetKoopaHit(int direction)
{
	if (state == GOOMBA_STATE_DIE 
		|| state == GOOMBA_STATE_DIE_BY_TAIL
		|| state == GOOMBA_STATE_DIE_BY_KOOPA
		) return;
	vx = direction * GOOMBA_WALKING_SPEED;
	SetState(GOOMBA_STATE_DIE_BY_KOOPA);
}
void CGoomba::GetTailHit(int direction)
{
	if (state == GOOMBA_STATE_DIE
		|| state == GOOMBA_STATE_DIE_BY_TAIL
		|| state == GOOMBA_STATE_DIE_BY_KOOPA
		) return;
	vx = direction * GOOMBA_WALKING_SPEED;
	SetState(GOOMBA_STATE_DIE_BY_TAIL);
}
void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (state == GOOMBA_STATE_WAITING) {
		float cx, cy;
		CGame::GetInstance()->GetCamPos(cx, cy);

		if (x - cx <= CGame::GetInstance()->GetBackBufferWidth() + GOOMBA_BBOX_WIDTH)
		{
			WakeUp();
		}
		return;
	}
	vy += ay * dt;
	vx += ax * dt;

	if (state == GOOMBA_STATE_DIE
		|| state == GOOMBA_STATE_DIE_BY_TAIL
		|| state == GOOMBA_STATE_DIE_BY_KOOPA
		)
	{
		OnNoCollision(dt);
		if (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) isDeleted = true;
		return;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = ID_ANI_GOOMBA_WALKING;
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		aniId = ID_ANI_GOOMBA_DIE;
		break;
	case GOOMBA_STATE_DIE_BY_KOOPA:
	case GOOMBA_STATE_DIE_BY_TAIL:
		aniId = ID_ANI_GOOMBA_DIE_BY_TAIL;
		break;
	case GOOMBA_STATE_WALKING:
		aniId = ID_ANI_GOOMBA_WALKING;
		break;
	case GOOMBA_STATE_WAITING:
		return;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
}

void CGoomba::SetState(int _state)
{
	CGameObject::SetState(_state);
	switch (_state)
	{
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
			break;
		case GOOMBA_STATE_DIE_BY_TAIL:
			die_start = GetTickCount64();
			vy = GOOMBA_DIE_SPEED_BY_TAIL;
			ay = GOOMBA_GRAVITY;
			break;
		case GOOMBA_STATE_DIE_BY_KOOPA:
			die_start = GetTickCount64();
			vy = GOOMBA_DIE_SPEED_BY_KOOPA;
			ay = GOOMBA_GRAVITY;
			break;
		case GOOMBA_STATE_WAITING:
			vx = 0;
			vy = 0;
			break;
	}
}
