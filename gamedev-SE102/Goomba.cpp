#include "ParaGoomba.h"
#include "debug.h"
#include "Game.h"
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
	if (dynamic_cast<CParaGoomba*>(e->obj)) {
		if (e->obj->GetState() == GOOMBA_STATE_PARA) return;
		OnCollisionWithGoomba(e);
		return;
	}
	if (dynamic_cast<CGoomba*>(e->obj)) 
	{
		OnCollisionWithGoomba(e);
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
void CGoomba::GetDamage()
{
	SetState(GOOMBA_STATE_DIE);
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

	if ( (state==GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) )
	{
		isDeleted = true;
		return;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	if (state == GOOMBA_STATE_WAITING) return;
	int aniId = ID_ANI_GOOMBA_WALKING;
	if (state == GOOMBA_STATE_DIE) 
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	RenderBoundingBox();
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
		case GOOMBA_STATE_WAITING:
			vx = 0;
			vy = 0;
			break;
	}
}
