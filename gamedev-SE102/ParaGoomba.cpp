#include "ParaGoomba.h"
#include "debug.h"
#include "Game.h"
#include "Mario.h"
#include "PlayScene.h"
void CParaGoomba::Render()
{
	int aniId = ID_ANI_PARA_GOOMBA_WALKING;
	GetAniId(aniId);
	if (aniId != 0)CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CParaGoomba::RenderWhenMarioPaused()
{
	int aniId = ID_ANI_PARA_GOOMBA_WALKING;
	GetAniId(aniId);
	if (aniId != 0) CAnimations::GetInstance()->Get(aniId)->RenderCurrentFrame(x, y);
}

void CParaGoomba::GetAniId(int& aniId)
{
	if (state == GOOMBA_STATE_WAITING)
	{
		aniId = 0;
		return;
	}
	
	if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_PARA_GOOMBA_DIE;
		return;
	}
	if (state == GOOMBA_STATE_PARA) {
		if (currentStep == 0) aniId = ID_ANI_PARA_GOOMBA_WALKING_WING;
		else if (currentStep == PARA_GOOMBA_TOTALSTEPS - 1) aniId = ID_ANI_PARA_GOOMBA_FLY;
		else aniId = ID_ANI_PARA_GOOMBA_JUMP;
		return;
	}
	if (state == GOOMBA_STATE_DIE_BY_TAIL || state == GOOMBA_STATE_DIE_BY_KOOPA)
		aniId = ID_ANI_PARA_GOOMBA_DIE_BY_TAIL;
}

void CParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	vy += ay * dt;
	if (state == GOOMBA_STATE_PARA)
	{
		if (!isChase) {
			float cx, cy;
			CGame::GetInstance()->GetCamPos(cx, cy);
			if (x - cx > CGame::GetInstance()->GetBackBufferWidth()) {
				SetState(GOOMBA_STATE_WAITING);
				return;
			}
		}
		ULONGLONG deltaTime = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetDeltaTime(timeStep);
		switch (currentStep)
		{
		case 0:
			if (deltaTime >= PARA_GOOMBA_WALK_TIMEOUT) {
				vy = -PARA_GOOMBA_JUMP_SPEED;
				vx = direction * GOOMBA_WALKING_SPEED;
				currentStep++;
			}
			break;
		case 1:
		case 2:
			if (isOnPlatform) {
				vy = -PARA_GOOMBA_JUMP_SPEED;
				vx = direction * GOOMBA_WALKING_SPEED;
				currentStep++;
			}
			break;
		case 3:
			if (isOnPlatform) {
				vy = -PARA_GOOMBA_JUMP_SPEED;
				vx = direction * GOOMBA_WALKING_SPEED;
				ay = GOOMBA_GRAVITY / 3.0f;
				currentStep++;
			}
			break;
		case 4:
			if (isOnPlatform) StartFisrtStep();
			break;
			
		}
		CCollision::GetInstance()->Process(this, dt, coObjects);
		return;
	}
	else CGoomba::Update(dt, coObjects);
	
}

void CParaGoomba::SetState(int _state)
{
	if (_state == GOOMBA_STATE_PARA) {
		chaseCount = 0;
		isChase = true;
		vx = -GOOMBA_WALKING_SPEED;
	}
	else if (_state == GOOMBA_STATE_WAITING) {
		SetPosition(startX, startY +100);
	}
	CGoomba::SetState(_state);
}

void CParaGoomba::WakeUp()
{
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	if (x - cx < CGame::GetInstance()->GetBackBufferWidth()) return;
	SetState(GOOMBA_STATE_PARA);
	SetPosition(startX, startY);
	StartFisrtStep();
}

void CParaGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CGoomba*>(e->obj))
	{
		if (state != GOOMBA_STATE_PARA) OnCollisionWithGoomba(e);
	}
	if (dynamic_cast<CKoopa*>(e->obj)) {
		if (e->obj->GetState() == KOOPA_STATE_DIE) return;
		OnCollisionWithKoopa(e);
		return;
	}
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else if (e->nx != 0)
	{
		ReverseDirection();
	}
}

void CParaGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	isOnPlatform = false;
}

void CParaGoomba::StartFisrtStep()
{
	timeStep = GetTickCount64();
	currentStep = 0;
	float mx, my;
	((CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer())->GetPosition(mx, my);
	int _direction = x > mx ? -1 : 1;
	if (chaseCount == 0 || direction == _direction) {
		chaseCount = 1;
	}
	else chaseCount++;
	if (chaseCount >= PARA_GOOMBA_MAX_CHASE) {
		direction = 1;
		isChase = false;
	}
	else {
		direction = _direction;
		isChase = true;
	}
	
	vy = 0;
	vx = direction * GOOMBA_WALKING_SPEED;
	ay = GOOMBA_GRAVITY;
}

void CParaGoomba::GetStomped()
{
	if (state == GOOMBA_STATE_PARA) {
		ay = GOOMBA_GRAVITY;
		state = GOOMBA_STATE_WALKING;
		vy = 0;
	}
	else SetState(GOOMBA_STATE_DIE);
}
